// -*- mode:c++; tab-width:2; indent-tabs-mode:nil; c-basic-offset:2 -*-
/*
 *  Copyright 2010 ZXing authors. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <zxing/common/BitArray.h>

using std::vector;
using zxing::BitArray;

// VC++
using zxing::Ref;

int BitArray::makeArraySize(int size) {
  return (size + bitsPerWord-1) >> logBits;
}

BitArray::BitArray(int size_)
  : size(size_), bits(makeArraySize(size)) {}

BitArray::BitArray(): size(0), bits(1) {}

BitArray::~BitArray() {
}

int BitArray::getSize() const {
  return size;
}

void BitArray::setBulk(int i, int newBits) {
  bits[i >> logBits] = newBits;
}

void BitArray::clear() {
  int max = bits->size();
  for (int i = 0; i < max; i++) {
    bits[i] = 0;
  }
}

bool BitArray::isRange(int start, int end, bool value) {
  if (end < start) {
    throw IllegalArgumentException();
  }
  if (end == start) {
    return true; // empty range matches
  }
  end--; // will be easier to treat this as the last actually set bit -- inclusive
  int firstInt = start >> logBits;
  int lastInt = end >> logBits;
  for (int i = firstInt; i <= lastInt; i++) {
    int firstBit = i > firstInt ? 0 : start & bitsMask;
    int lastBit = i < lastInt ? (bitsPerWord-1) : end & bitsMask;
    int mask;
    if (firstBit == 0 && lastBit == (bitsPerWord-1)) {
      mask = -1;
    } else {
      mask = 0;
      for (int j = firstBit; j <= lastBit; j++) {
        mask |= 1 << j;
      }
    }
    
    // Return false if we're looking for 1s and the masked bits[i] isn't all 1s (that is,
    // equals the mask, or we're looking for 0s and the masked portion is not all 0s
    if ((bits[i] & mask) != (value ? mask : 0)) {
      return false;
    }
  }
  return true;
}

vector<int>& BitArray::getBitArray() {
  return bits->values();
}

void BitArray::reverse() {
  ArrayRef<int> newBits(bits->size());
  int size = this->size;
  for (int i = 0; i < size; i++) {
    if (get(size - i - 1)) {
      newBits[i >> logBits] |= 1 << (i & bitsMask);
    }
  }
  bits = newBits;
}

BitArray::Reverse::Reverse(Ref<BitArray> array_) : array(array_) {
  array->reverse();
}

BitArray::Reverse::~Reverse() {
  array->reverse();
}

namespace {
  // N.B.: This only works for 32 bit ints ...
  int numberOfTrailingZeros(int i) {
    // HD, Figure 5-14
    int y;
    if (i == 0) return 32;
    int n = 31;
    y = i <<16; if (y != 0) { n = n -16; i = y; }
    y = i << 8; if (y != 0) { n = n - 8; i = y; }
    y = i << 4; if (y != 0) { n = n - 4; i = y; }
    y = i << 2; if (y != 0) { n = n - 2; i = y; }
    return n - (((unsigned int)(i << 1)) >> 31);
  }
}

int BitArray::getNextSet(int from) {
  if (from >= size) {
    return size;
  }
  int bitsOffset = from >> logBits;
  int currentBits = bits[bitsOffset];
  // mask off lesser bits first
  currentBits &= ~((1 << (from & bitsMask)) - 1);
  while (currentBits == 0) {
    if (++bitsOffset == (int)bits->size()) {
      return size;
    }
    currentBits = bits[bitsOffset];
  }
  int result = (bitsOffset << logBits) + numberOfTrailingZeros(currentBits);
  return result > size ? size : result;
}

int BitArray::getNextUnset(int from) {
  if (from >= size) {
    return size;
  }
  int bitsOffset = from >> logBits;
  int currentBits = ~bits[bitsOffset];
  // mask off lesser bits first
  currentBits &= ~((1 << (from & bitsMask)) - 1);
  while (currentBits == 0) {
    if (++bitsOffset == (int)bits->size()) {
      return size;
    }
    currentBits = ~bits[bitsOffset];
  }
  int result = (bitsOffset << logBits) + numberOfTrailingZeros(currentBits);
  return result > size ? size : result;
}

void BitArray::ensureCapacity(int size) {
  if (size > bits->size() * 32) {
    ArrayRef<int> newBits(makeArraySize(size));
    memcpy(&newBits[0], &bits[0], sizeof(int) * bits->size());
    this->bits = newBits;
  }
}

int BitArray::getSizeInBytes() const {
  return (size + 7) / 8;
}

void BitArray::appendBit(bool bit) {
  ensureCapacity(size + 1);
  if (bit) {
    bits[size / 32] |= 1 << (size & 0x1F);
  }
  size++;
}

/**
 * Appends the least-significant bits, from value, in order from most-significant to
 * least-significant. For example, appending 6 bits from 0x000001E will append the bits
 * 0, 1, 1, 1, 1, 0 in that order.
 */
void BitArray::appendBits(int value, int numBits) {
  if (numBits < 0 || numBits > 32) {
    throw IllegalArgumentException("Num bits must be between 0 and 32");
  }
  ensureCapacity(size + numBits);
  for (int numBitsLeft = numBits; numBitsLeft > 0; numBitsLeft--) {
    appendBit(((value >> (numBitsLeft - 1)) & 0x01) == 1);
  }
}

void BitArray::appendBitArray(Ref<BitArray> other) {
  int otherSize = other->size;
  ensureCapacity(size + otherSize);
  for (int i = 0; i < otherSize; i++) {
    appendBit(other->get(i));
  }
}

void BitArray::xor_(Ref<BitArray> other) {
  if (bits->size() != other->bits->size()) {
    throw IllegalArgumentException("Sizes don't match");
  }
  for (int i = 0; i < bits->size(); i++) {
    // The last byte could be incomplete (i.e. not have 8 bits in
    // it) but there is no problem since 0 XOR 0 == 0.
    bits[i] ^= other->bits[i];
  }
}

/**
 *
 * @param bitOffset first bit to start writing
 * @param array array to write into. Bytes are written most-significant byte first. This is the opposite
 *  of the internal representation, which is exposed by {@link #getBitArray()}
 * @param offset position in array to start writing
 * @param numBytes how many bytes to write
 */
void
BitArray::toBytes(int bitOffset,
                         zxing::ArrayRef<int8_t> array,
                         int offset,
                         int numBytes) {
  for (int i = 0; i < numBytes; i++) {
    int theByte = 0;
    for (int j = 0; j < 8; j++) {
      if (get(bitOffset)) {
        theByte |= 1 << (7 - j);
      }
      bitOffset++;
    }
    array[offset + i] = (int8_t) theByte;
  }
}

