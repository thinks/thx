//------------------------------------------------------------------------------
//
// Contributors: 
//             1) Tommy Hinks
//
//------------------------------------------------------------------------------

#ifndef THX_HASHING_HPP_INCLUDED
#define THX_HASHING_HPP_INCLUDED

#include "thx_types.h"

//------------------------------------------------------------------------------

namespace thx
{

// murmur_hash
// -----------
//! DOCS

template<typename K>
thx::uint32 
murmur_hash(const K *key, int len, thx::uint32 seed)
{
	// 'm' and 'r' are mixing constants generated offline.
	// They're not really 'magic', they just happen to work well.

	const thx::uint32 m = 0x5bd1e995;
	const thx::int32 r = 24;

	// Initialize the hash to a 'random' value

	thx::uint32 h = seed ^ len;

	// Mix 4 bytes at a time into the hash

	//const unsigned char *data = (const unsigned char *)key;
	const thx::uint8 *data = reinterpret_cast<const thx::uint8>(key);

	while(len >= 4)
	{
#ifdef PLATFORM_BIG_ENDIAN
		//unsigned int k = (data[0]) + (data[1] << 8) + (data[2] << 16) + (data[3] << 24);
		thx::uint32 k = 
			(data[0]) + 
			(data[1] << 8) + 
			(data[2] << 16) + 
			(data[3] << 24);
#else
		//thx::uint32 k = *(unsigned int *)data;
		thx::uint32 k = *reinterpret_cast<thx::uint32*>(data);

#endif

		k *= m;
		k ^= k >> r;
		k *= m;

		h *= m;
		h ^= k;

		data += 4;
		len -= 4;
	}

	// Handle the last few bytes of the input array

	switch(len)
	{
	case 3: sh ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
			h *= m;
	};

	// Do a few final mixes of the hash to ensure the last few
	// bytes are well-incorporated.

	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;

	return h;
}


// invert_shift_xor
// ----------------
//! Inverts a (h ^= h >> s) operation with 8 <= s <= 16

thx::uint32 
invert_shift_xor(thx::uint32 hs, thx::uint32 s)
{
	//XENSURE(s >= 8 && s <= 16);

	//unsigned hs0 = hs >> 24;
	//unsigned hs1 = (hs >> 16) & 0xff;
	//unsigned hs2 = (hs >> 8) & 0xff;
	//unsigned hs3 = hs & 0xff;

	//unsigned h0 = hs0;
	//unsigned h1 = hs1 ^ (h0 >> (s-8));
	//unsigned h2 = (hs2 ^ (h0 << (16-s)) ^ (h1 >> (s-8))) & 0xff;
	//unsigned h3 = (hs3 ^ (h1 << (16-s)) ^ (h2 >> (s-8))) & 0xff;

	thx::uint32 hs0 = hs >> 24;
	thx::uint32 hs1 = (hs >> 16) & 0xff;
	thx::uint32 hs2 = (hs >> 8) & 0xff;
	thx::uint32 hs3 = hs & 0xff;

	thx::uint32 h0 = hs0;
	thx::uint32 h1 = hs1 ^ (h0 >> (s-8));
	thx::uint32 h2 = (hs2 ^ (h0 << (16-s)) ^ (h1 >> (s-8))) & 0xff;
	thx::uint32 h3 = (hs3 ^ (h1 << (16-s)) ^ (h2 >> (s-8))) & 0xff;

	return (h0<<24) + (h1<<16) + (h2<<8) + h3;
}


// murmur_hash_inverse
// -------------------
//! DOCS

thx::uint32 
murmur_hash_inverse(thx::uint32 h, thx::uint32 seed)
{
	const thx::uint32 m = 0x5bd1e995;
	const thx::uint32 minv = 0xe59b19bd;//Multiplicative inv. of m under % 2^32
	const thx::int32 r = 24;

	h = invert_shift_xor(h, 15);
	h *= minv;
	h = invert_shift_xor(h, 13);

	thx::uint32 hforward = seed ^ 4;
	hforward *= m;
	thx::uint32 k = hforward ^ h;
	k *= minv;
	k ^= k >> r;
	k *= minv;

	#ifdef PLATFORM_BIG_ENDIAN
		//thx::int8 *data = (char *)&k;
		thx::int8 *data = reinterpret_cast<thx::int8*>(&k);
		k = (data[0]) + (data[1] << 8) + (data[2] << 16) + (data[3] << 24);
	#endif

	return k;
}


// murmur_hash_64
// --------------
//! DOCS

template<typename K>
thx::uint64 
murmur_hash_64(const K *key, int len, thx::uint64 seed)
{
	const thx::uint64 m = 0xc6a4a7935bd1e995ULL;
	const thx::int32 r = 47;

	thx::uint64 h = seed ^ (len * m);

	//const thx::uint64 * data = (const uint64 *)key;
	const thx::uint64 *data = reinterpret_cast<const thx::uint64*>(key);
	const thx::uint64 *end = data + (len/8);

	while(data != end)
	{
		#ifdef PLATFORM_BIG_ENDIAN
			thx::uint64 k = *data++;
			//char *p = (char *)&k;
			thx::int8 = reinterpret_cast<thx::int8>(&k);
			thx::int8 c;
			c = p[0]; p[0] = p[7]; p[7] = c;
			c = p[1]; p[1] = p[6]; p[6] = c;
			c = p[2]; p[2] = p[5]; p[5] = c;
			c = p[3]; p[3] = p[4]; p[4] = c;
		#else
			thx::uint64 k = *data++;
		#endif

		k *= m;
		k ^= k >> r;
		k *= m;
		
		h ^= k;
		h *= m;
	}

	//const thx::uint8 *data2 = (const unsigned char*)data;
	const thx::uint8 *data2 = reinterpret_cast<const thx::uint8*>(data);

	switch(len & 7)
	{
	case 7: h ^= thx::uint64(data2[6]) << 48;
	case 6: h ^= thx::uint64(data2[5]) << 40;
	case 5: h ^= thx::uint64(data2[4]) << 32;
	case 4: h ^= thx::uint64(data2[3]) << 24;
	case 3: h ^= thx::uint64(data2[2]) << 16;
	case 2: h ^= thx::uint64(data2[1]) << 8;
	case 1: h ^= thx::uint64(data2[0]);
			h *= m;
	};
 
	h ^= h >> r;
	h *= m;
	h ^= h >> r;

	return h;
}

thx::uint64 
murmur_hash_64_inverse(thx::uint64 h, thx::uint64 seed)
{
	const thx::uint64 m = 0xc6a4a7935bd1e995ULL;
	const thx::uint64 minv = 0x5f7a0ea7e59b19bdULL; // Multiplicative inverse of m under % 2^64
	const thx::int32 r = 47;

	h ^= h >> r;
	h *= minv;
	h ^= h >> r;
	h *= minv;

	thx::uint64 hforward = seed ^ (8 * m);
	thx::uint64 k = h ^ hforward;

	k *= minv;
	k ^= k >> r;
	k *= minv;

#ifdef PLATFORM_BIG_ENDIAN
	//char *p = (char *)&k;
	thx::int8 *p = reinterpret_cast<thx::int8>(&k);
	thx::int8 c;
	c = p[0]; p[0] = p[7]; p[7] = c;
	c = p[1]; p[1] = p[6]; p[6] = c;
	c = p[2]; p[2] = p[5]; p[5] = c;
	c = p[3]; p[3] = p[4]; p[4] = c;
#endif
	
	return k;
}

}	// Namespace: thx.

#endif // THX_HASHING_HPP_INCLUDED