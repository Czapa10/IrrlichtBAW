// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_MESH_MANIPULATOR_H_INCLUDED__
#define __C_MESH_MANIPULATOR_H_INCLUDED__

#include "irr/asset/IMeshManipulator.h"

namespace irr
{
namespace asset
{

//! An interface for easy manipulation of meshes.
/** Scale, set alpha value, flip surfaces, and so on. This exists for fixing
problems with wrong imported or exported meshes quickly after loading. It is
not intended for doing mesh modifications and/or animations during runtime.
*/
class CMeshManipulator : public IMeshManipulator
{
		struct SAttrib
		{
			E_FORMAT type;
			E_FORMAT prevType;
			size_t size;
			E_VERTEX_ATTRIBUTE_ID vaid;
			size_t offset;

			SAttrib() : type(EF_UNKNOWN), size(0), vaid(EVAI_COUNT) {}

			friend bool operator>(const SAttrib& _a, const SAttrib& _b) { return _a.size > _b.size; }
		};
		struct SAttribTypeChoice
		{
			E_FORMAT type;
		};

	public:
		static core::smart_refctd_ptr<ICPUMeshBuffer> createMeshBufferFetchOptimized(const ICPUMeshBuffer* _inbuffer);

	private:
		friend class IMeshManipulator;
		//! Copies only member variables not being pointers to another dynamically allocated irr::IReferenceCounted derivatives.
		//! Purely helper function. Not really meant to be used outside createMeshBufferDuplicate().
		template<typename T>
		static void copyMeshBufferMemberVars(T* _dst, const T* _src);

		template<typename IdxT>
		static void _filterInvalidTriangles(ICPUMeshBuffer* _input);

		//! Meant to create 32bit index buffer from subrange of index buffer containing 16bit indices. Remember to set to index buffer offset to 0 after mapping buffer resulting from this function.
		static inline core::smart_refctd_ptr<ICPUBuffer> create32BitFrom16BitIdxBufferSubrange(const uint16_t* _in, size_t _idxCount)
		{
			if (!_in)
				return nullptr;

			auto out = core::make_smart_refctd_ptr<ICPUBuffer>(sizeof(uint32_t) * _idxCount);

			auto* outPtr = reinterpret_cast<uint32_t*>(out->getPointer());

			for (size_t i = 0; i < _idxCount; ++i)
				outPtr[i] = _in[i];

			return out;
		}

		static core::vector<core::vectorSIMDf> findBetterFormatF(E_FORMAT* _outType, size_t* _outSize, E_FORMAT* _outPrevType, const ICPUMeshBuffer* _meshbuffer, E_VERTEX_ATTRIBUTE_ID _attrId, const SErrorMetric& _errMetric);

		struct SIntegerAttr
		{
			uint32_t pointer[4];
		};
		static core::vector<SIntegerAttr> findBetterFormatI(E_FORMAT* _outType, size_t* _outSize, E_FORMAT* _outPrevType, const ICPUMeshBuffer* _meshbuffer, E_VERTEX_ATTRIBUTE_ID _attrId, const SErrorMetric& _errMetric);

		//E_COMPONENT_TYPE getBestTypeF(bool _normalized, E_COMPONENTS_PER_ATTRIBUTE _cpa, size_t* _outSize, E_COMPONENTS_PER_ATTRIBUTE* _outCpa, const float* _min, const float* _max) const;
		static E_FORMAT getBestTypeI(E_FORMAT _originalType, size_t* _outSize, const uint32_t* _min, const uint32_t* _max);
		static core::vector<SAttribTypeChoice> findTypesOfProperRangeF(E_FORMAT _type, size_t _sizeThreshold, const float* _min, const float* _max, const SErrorMetric& _errMetric);

		//! Calculates quantization errors and compares them with given epsilon.
		/** @returns false when first of calculated errors goes above epsilon or true if reached end without such. */
		static bool calcMaxQuantizationError(const SAttribTypeChoice& _srcType, const SAttribTypeChoice& _dstType, const core::vector<core::vectorSIMDf>& _data, const SErrorMetric& _errMetric);

		template<typename T>
		static inline core::smart_refctd_ptr<ICPUBuffer> triangleStripsToTriangles(const void* _input, size_t _idxCount)
		{
			const size_t outputSize = (_idxCount - 2) * 3;

			auto output = core::make_smart_refctd_ptr<ICPUBuffer>(sizeof(T)*outputSize);
			T* iptr = (T*)_input;
			T* optr = (T*)output->getPointer();
			for (size_t i = 0, j = 0; i < outputSize; j += 2)
			{
				optr[i++] = iptr[j + 0];
				optr[i++] = iptr[j + 1];
				optr[i++] = iptr[j + 2];
				if (i == outputSize)
					break;
				optr[i++] = iptr[j + 2];
				optr[i++] = iptr[j + 1];
				optr[i++] = iptr[j + 3];
			}
			return output;
		}

		template<typename T>
		static inline core::smart_refctd_ptr<ICPUBuffer> trianglesFanToTriangles(const void* _input, size_t _idxCount)
		{
			const size_t outputSize = ((_idxCount - 1) / 2) * 3;

			auto output = core::make_smart_refctd_ptr<ICPUBuffer>(sizeof(T)*outputSize);
			const T* iptr = reinterpret_cast<const T*>(_input);
			T* optr = reinterpret_cast<T*>(output->getPointer());
			for (size_t i = 0, j = 1; i < outputSize; j += 2)
			{
				optr[i++] = iptr[0];
				optr[i++] = iptr[j];
				optr[i++] = iptr[j + 1];
			}
			return output;
		}
};

} // end namespace scene
} // end namespace irr


#endif
