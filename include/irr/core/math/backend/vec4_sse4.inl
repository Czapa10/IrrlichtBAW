
// constructors
vec4::vec4() { 
	_mm_store_ps(ptr, _mm_setzero_ps()); 
}
vec4::vec4(float scalar) {
	_mm_store_ps(ptr, _mm_set1_ps(scalar));
}
vec4::vec4(float x, float y, float z, float w) {
	_mm_store_ps(ptr, _mm_setr_ps(x, y, z, w)); 
};
vec4::vec4(float* const memory) { 
	_mm_store_ps(ptr, _mm_loadu_ps(memory)); 
}
vec4::vec4(float* const memory, aligned_t) {
	_mm_store_ps(ptr, _mm_load_ps(memory)); 
}
vec4::vec4(const f32x4& m) {
	_mm_store_ps(ptr, m);
}
vec4::vec4(const vec4& other) {
	_mm_store_ps(ptr, other.getAsRegister());
}

// getters
f32x4 vec4::getAsRegister() const {
	return _mm_load_ps(ptr);
}

// vec vec operators
vec4 operator+(vec4 a, vec4 b) {
	return _mm_add_ps(a.getAsRegister(), b.getAsRegister());
}
vec4 operator-(vec4 a, vec4 b) {
	return _mm_sub_ps(a.getAsRegister(), b.getAsRegister()) ;
}
inline vec4 operator*(vec4 a, vec4 b) {
	return _mm_mul_ps(a.getAsRegister(), b.getAsRegister());
}
vec4 operator/(vec4 a, vec4 b) {
	return _mm_div_ps(a.getAsRegister(), b.getAsRegister()); 
}
inline vec4& operator+=(vec4& a, vec4 b) {
	_mm_store_ps(a.ptr, _mm_add_ps(a.getAsRegister(), b.getAsRegister()));
	return a;
} 
inline vec4& operator-=(vec4& a, vec4 b) {
	_mm_store_ps(a.ptr, _mm_sub_ps(a.getAsRegister(), b.getAsRegister()));
	return a;
} 
inline vec4& operator*=(vec4& a, vec4 b) {
	_mm_store_ps(a.ptr, _mm_mul_ps(a.getAsRegister(), b.getAsRegister()));
	return a;
} 
inline vec4& operator/=(vec4& a, vec4 b) {
	_mm_store_ps(a.ptr, _mm_div_ps(a.getAsRegister(), b.getAsRegister()));
	return a;
}

// vec scalar operators
vec4 operator/(vec4 v, float scalar) {
	return _mm_div_ps(v.getAsRegister(), _mm_set1_ps(scalar));
}
vec4 operator/(float scalar, vec4 b) {
	return _mm_div_ps(_mm_set1_ps(scalar), b.getAsRegister());
}
vec4 operator*(vec4 v, float scalar) {
	return _mm_mul_ps(v.getAsRegister(), _mm_set1_ps(scalar));
}
vec4 operator*(float scalar, vec4 v) {
	return v * scalar;
}

