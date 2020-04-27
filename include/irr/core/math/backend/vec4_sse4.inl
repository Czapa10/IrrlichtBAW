
//namespace impl
//{

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
f32x4 vec4::getAsRegister() const {
	return _mm_load_ps(ptr);
}


//}
