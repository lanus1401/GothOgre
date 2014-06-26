#ifndef GOTHOGRE_ZEN_ARCHIVE_IMPL_BINARY_H
#define GOTHOGRE_ZEN_ARCHIVE_IMPL_BINARY_H

#include "GothOgre_ZenArchive_Impl.h"

namespace GothOgre
{
	// ����������� ������� ����� ������
	class ZenArchiveImplBinary : public ZenArchiveImpl
	{
	public:
		ZenArchiveImplBinary();
		virtual ~ZenArchiveImplBinary();

		virtual void readHeader();
		virtual void writeHeader();
		virtual void readFooter();
		virtual void writeFooter();

	public:
		// �������� � ����� �������� - ����� ����� (4 �����)
		virtual void writeInt(const String& _entryName, int _value);

		// �������� � ����� �������� - ����
		virtual void writeByte(const String& _entryName, uchar _value);
		
		// �������� � ����� �������� - ����� (2 �����)
		virtual void writeWord(const String& _entryName, ushort _value);

		// �������� � ����� �������� - ������������ �������� (4 �����)
		virtual void writeFloat(const String& _entryName, float _value);

		// �������� � ����� �������� - ���������� ��������
		virtual void writeBool(const String& _entryName, bool _value);

		// �������� � ����� �������� - ������
		virtual void writeString(const String& _entryName, const String& _value);

		// �������� � ����� �������� - ������
		virtual void writeVec3(const String& _entryName, const Vec3& _value);

		// �������� � ����� �������� - ����
		virtual void writeColor(const String& _entryName, const Color& _value);
		
		// �������� � ����� �������� - ������ ����
		virtual void writeRaw(const String& _entryName, const void* _rawData, size_t _sizeInBytes);

		// �������� � ����� �������� - ������ ������������ �����
		virtual void writeRawFloat(const String& _entryName, const float* _rawData, size_t _sizeInBytes);

		// �������� � ����� �������� - ������������;
		// ������ �������� ��������� ����� �������� ������������,
		// ����� ����� � �������.
		virtual void writeEnum(const String& _entryName, int _value);

		// ������ ������ ����� � �����.
		virtual ZenArchive::Chunk* writeChunkBegin(const String& _chunkName, const String& _chunkType, ushort _objectVersion, ulong objectIndex);
		
		// ��������� ������ ����� � �����.
		virtual void writeChunkEnd(ZenArchive::Chunk* _chunk);

	public:
		// ��������� �� ������ �������� - ����� ����� (4 �����)
		virtual bool readInt(const String& _entryName, int& _outValue);

		// ��������� �� ������ �������� - ����
		virtual bool readByte(const String& _entryName, uchar& _outValue);

		// ��������� �� ������ �������� - ����� (2 �����)
		virtual bool readWord(const String& _entryName, ushort& _outValue);

		// ��������� �� ������ �������� - ������������ ����� (4 �����)
		virtual bool readFloat(const String& _entryName, float& _outValue);

		// ��������� �� ������ �������� - ���������� ��������
		virtual bool readBool(const String& _entryName, bool& _outValue);

		// ��������� �� ������ �������� - ������
		virtual bool readString(const String& _entryName, String& _outValue);

		// ��������� �� ������ �������� - ������
		virtual bool readVec3(const String& _entryName, Vec3& _outValue);

		// ��������� �� ������ �������� - ����
		virtual bool readColor(const String& _entryName, Color& _outValue);

		// ��������� �� ������ �������� - ������������
		virtual bool readEnum(const String& _entryName, int& _outValue);

		// ��������� �� ������ �������� - ������ ����
		virtual size_t readRaw(const String& _entryName, void* _rawData, size_t _sizeInBytes);

		// ��������� �� ������ �������� - ������ ������������ �����
		virtual size_t readRawFloat(const String& _entryName, float* _rawData, size_t _sizeInBytes);

		// ��������� �� ������ ���� � ��������� ������.
		// ���� ���� � ��������� ������ �� ������, ������������ FALSE.
		virtual ZenArchive::Chunk* readChunkBegin(const String& _chunkName);

		// ��������� ����� ����� �� ������, �.�. ���������� ��� 
		// �� ����� �������� ����� ������������.
		virtual void readChunkEnd(ZenArchive::Chunk* _chunk);

	private:
		class Chunk : public ZenArchive::Chunk
		{
			friend class ZenArchiveImplBinary;
			Chunk() {mChunkSize = 0;}

			size_t mChunkSize;
		};

	private:
		size_t	mPosNumObjects;
		String  mCurrentLine;
		String  mTempStr;
	};

} // namespace GothOgre

#endif // GOTHOGRE_ZEN_ARCHIVE_IMPL_BINARY_H