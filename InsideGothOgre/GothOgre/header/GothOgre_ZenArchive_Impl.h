#ifndef GOTHOGRE_ZEN_ARCHIVE_IMPL_H
#define GOTHOGRE_ZEN_ARCHIVE_IMPL_H

#include "GothOgre_ZenArchive.h"
#include "GothOgre_DataStreamEx.h"

namespace GothOgre
{
	// ����������� ������� ����� ������
	class ZenArchiveImpl
	{
	protected:
		typedef ZenArchive::Vec3 Vec3;
		typedef ZenArchive::Color Color;
		typedef ZenArchive::ObjectReadList ObjectReadList;
		typedef ZenArchive::ObjectWriteMap ObjectWriteMap;

	public:
		ZenArchiveImpl() {}
		virtual ~ZenArchiveImpl() {}

		void init( const DataStreamExPtr& _dataStream, ZenArchiveFlags _flags, ObjectReadList* _objectReadList )
		{
			mDataStream = _dataStream;
			mName = mDataStream->getName();
			mFlags = _flags;
			mObjectReadList = _objectReadList;
		}

		void init( const DataStreamExPtr& _dataStream, ZenArchiveFlags _flags, ObjectWriteMap* _objectWriteMap )
		{
			mDataStream = _dataStream;
			mName = mDataStream->getName();
			mFlags = _flags;
			mObjectWriteMap = _objectWriteMap;
		}

		virtual void readHeader() {}
		virtual void writeHeader() {}
		virtual void readFooter() {}
		virtual void writeFooter() {}

	public:
		// �������� � ����� �������� - ����� ����� (4 �����)
		virtual void writeInt(const String& _entryName, int _value) = 0;

		// �������� � ����� �������� - ����
		virtual void writeByte(const String& _entryName, uchar _value) = 0;
		
		// �������� � ����� �������� - ����� (2 �����)
		virtual void writeWord(const String& _entryName, ushort _value) = 0;

		// �������� � ����� �������� - ������������ �������� (4 �����)
		virtual void writeFloat(const String& _entryName, float _value) = 0;

		// �������� � ����� �������� - ���������� ��������
		virtual void writeBool(const String& _entryName, bool _value) = 0;

		// �������� � ����� �������� - ������
		virtual void writeString(const String& _entryName, const String& _value) = 0;

		// �������� � ����� �������� - ������
		virtual void writeVec3(const String& _entryName, const Vec3& _value) = 0;

		// �������� � ����� �������� - ����
		virtual void writeColor(const String& _entryName, const Color& _value) = 0;
		
		// �������� � ����� �������� - ������ ����
		virtual void writeRaw(const String& _entryName, const void* _rawData, size_t _sizeInBytes) = 0;

		// �������� � ����� �������� - ������ ������������ �����
		virtual void writeRawFloat(const String& _entryName, const float* _rawData, size_t _sizeInBytes) = 0;

		// �������� � ����� �������� - ������������;
		// ������ �������� ��������� ����� �������� ������������,
		// ����� ����� � �������.
		virtual void writeEnum(const String& _entryName, int _value) = 0;

		// ������ ������ ����� � �����.
		virtual ZenArchive::Chunk* writeChunkBegin(const String& _chunkName, const String& _chunkType, ushort _objectVersion, ulong _objectIndex) = 0;
		
		// ��������� ������ ����� � �����.
		virtual void writeChunkEnd(ZenArchive::Chunk* _chunk) = 0;

	public:
		// ��������� �� ������ �������� - ����� ����� (4 �����)
		virtual bool readInt(const String& _entryName, int& _outValue) = 0;

		// ��������� �� ������ �������� - ����
		virtual bool readByte(const String& _entryName, uchar& _outValue) = 0;

		// ��������� �� ������ �������� - ����� (2 �����)
		virtual bool readWord(const String& _entryName, ushort& _outValue) = 0;

		// ��������� �� ������ �������� - ������������ ����� (4 �����)
		virtual bool readFloat(const String& _entryName, float& _outValue) = 0;

		// ��������� �� ������ �������� - ���������� ��������
		virtual bool readBool(const String& _entryName, bool& _outValue) = 0;

		// ��������� �� ������ �������� - ������
		virtual bool readString(const String& _entryName, String& _outValue) = 0;

		// ��������� �� ������ �������� - ������
		virtual bool readVec3(const String& _entryName, Vec3& _outValue) = 0;

		// ��������� �� ������ �������� - ����
		virtual bool readColor(const String& _entryName, Color& _outValue) = 0;

		// ��������� �� ������ �������� - ������������
		virtual bool readEnum(const String& _entryName, int& _outValue) = 0;

		// ��������� �� ������ �������� - ������ ����
		virtual size_t readRaw(const String& _entryName, void* _rawData, size_t _sizeInBytes) = 0;

		// ��������� �� ������ �������� - ������ ������������ �����
		virtual size_t readRawFloat(const String& _entryName, float* _rawData, size_t _sizeInBytes) = 0;

		// ��������� �� ������ ���� � ��������� ������.
		// ���� ���� � ��������� ������ �� ������, ������������ nullptr.
		virtual ZenArchive::Chunk* readChunkBegin(const String& _chunkName) = 0;

		// ��������� ����� ����� �� ������, �.�. ���������� ��� 
		// �� ����� �������� ����� ������������.
		virtual void readChunkEnd(ZenArchive::Chunk* _chunk) = 0;

	protected:
		String           mName;
		DataStreamExPtr	 mDataStream;
		ZenArchiveFlags  mFlags;
		ObjectReadList*  mObjectReadList;
		ObjectWriteMap*  mObjectWriteMap;
	};

} // namespace GothOgre

#endif // GOTHOGRE_ZEN_ARCHIVE_IMPL_H