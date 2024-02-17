#pragma once

struct FColor
{
	unsigned char R, G, B, A;

	FColor() : R(0), G(0), B(0), A(0) {};

	explicit FColor(const unsigned char& val) : R(val), G(val), B(val), A(val) {};

	FColor(const unsigned char& color, unsigned char alpha) : R(color), G(color), B(color), A(alpha) {};

	FColor(const unsigned char& r, const unsigned char& g, const unsigned char& b) : R(r), G(g), B(b), A(255) {};

	FColor(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a) : R(r), G(g), B(b), A(a) {};

	static FColor const Zero() { return FColor(0); }

	static FColor const White() { return FColor(255); }

	static FColor const Red() { return FColor(255, 0, 0); }

	static FColor const Green() { return FColor(0, 255, 0); }

	static FColor const Blue() { return FColor(0, 0, 255); }

	static FColor const Random() { return FColor(rand() % 255, rand() % 255, rand() % 255); }

	bool operator==(const FColor& Other) const
	{
		return R == Other.R && G == Other.G && B == Other.B && A == Other.A;
	}

};