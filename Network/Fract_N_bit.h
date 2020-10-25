#pragma once

#include<cstdint>

template<int Bits>
class Fract_N_bit {
	struct data_t {
		int64_t data : Bits;

		data_t(uint64_t vl) {
			data = vl;
		}
		data_t() {
			data = 0;
		}
	};
	data_t data; // Bits-bit bit-field :)
public:
	static const uint64_t MAX=(((uint64_t)1 << (Bits-1)) - 1);
	static const uint64_t MIN=( (uint64_t)(int64_t(-1)) << (Bits-1));
	static const int64_t RND = (1<<(Bits-2));
	Fract_N_bit(int64_t value) {
		if (value > int64_t(MAX)) 
			data = MAX;
		else if (value < int64_t(MIN)) 
			data = MIN;
		else 
			data = value;
	}
	Fract_N_bit(const Fract_N_bit&) = default;
	Fract_N_bit& operator=(const Fract_N_bit& second) {
		this->data = second.data;
		return *this;
	}

	operator int() {
		return int(data.data);
	}
	Fract_N_bit operator* (const Fract_N_bit& second) const {
		int64_t first_op = this->data.data;
		int64_t second_op = second.data.data;
		int64_t res = (first_op * second_op);
		res = (res + RND) >> (Bits-1); // rounding ASYM
		return res;
	}
	Fract_N_bit operator+ (const Fract_N_bit& second) const {
		int64_t first_op = this->data.data;
		int64_t second_op = second.data.data;
		int64_t res = (first_op + second_op);
		return res;
	}
	Fract_N_bit operator- (const Fract_N_bit& second) const {
		int64_t first_op = this->data.data;
		int64_t second_op = second.data.data;
		int64_t res = (first_op - second_op);
		return res;
	}
	Fract_N_bit MUL_ACC (const Fract_N_bit& first, const Fract_N_bit& second) const {
		int64_t sum_op = this->data.data;
		int64_t first_op = first.data.data;
		int64_t second_op = second.data.data;
		sum_op <<= (Bits - 1);
		int64_t res = (first_op * second_op)+sum_op;
		res = (res + RND) >> (Bits - 1); // rounding ASYM
		return res;
	}
	void MUL_ADD_ACC(const Fract_N_bit& first, const Fract_N_bit& second, const Fract_N_bit& third) {
		int64_t sum_op = this->data.data;
		int64_t first_op = first.data.data;
		int64_t second_op = second.data.data;
		int64_t third_op = third.data.data;
		sum_op <<= (Bits - 1);
		third_op <<= (Bits - 1);
		int64_t res = (first_op * second_op) + third_op + sum_op;
		res = (res + RND) >> (Bits - 1); // rounding ASYM
		*this = Fract_N_bit(res);
	}
};