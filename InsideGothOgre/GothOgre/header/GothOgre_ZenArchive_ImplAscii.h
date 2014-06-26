#ifndef GOTHOGRE_ZEN_ARCHIVE_IMPL_ASCII_H
#define GOTHOGRE_ZEN_ARCHIVE_IMPL_ASCII_H

#include "GothOgre_ZenArchive_Impl.h"
#include "GothOgre_StrStream.h"

namespace GothOgre
{
	// ����������� ������� ����� ������
	class ZenArchiveImplAscii : public ZenArchiveImpl
	{
	public:
		ZenArchiveImplAscii();
		virtual ~ZenArchiveImplAscii();

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
		void writeEntryBegin(const String& _entryName, const String& _entryType);
		void writeEntryEnd();
		bool readEntry(const String& _entryName);
		void findChunkEnd();
		bool parseEntry();
		bool parseChunkBegin();

		struct SkippedEntry
		{
			String entryValue;
		};

		struct SkippedSubchunk
		{
			String chunkName;
			String chunkType;
			size_t chunkPos;
			size_t dataPos;
			ushort objectVersion;
			ulong  objectIndex;
		};
		
		class Chunk : public ZenArchive::Chunk
		{
			Chunk() {mStoredPos = -1;}
			friend class ZenArchiveImplAscii;

			map<String, SkippedEntry>::type		mSkippedEntries;
			map<String, SkippedSubchunk>::type	mSkippedSubchunks;
			size_t								mStoredPos;
		};

		struct ReadChunk
		{
			String chunkName;
			String chunkType;
			ushort objectVersion;
			ulong  objectIndex;
		};

		struct ReadEntry
		{
			String name;
			String value;
		};

		static const String TYPENAME_INT;       // "int"
		static const String TYPENAME_BOOL;      // "bool"
		static const String TYPENAME_STRING;    // "string"
		static const String TYPENAME_FLOAT;     // "float"
		static const String TYPENAME_RAW;       // "raw"
		static const String TYPENAME_RAW_FLOAT; // "rawFloat"
		static const String TYPENAME_COLOR;     // "color"
		static const String TYPENAME_VEC3;      // "vec3"
		static const String TYPENAME_ENUM;      // "enum"

	private:
		size_t			mNumObjectsPos;
		size_t			mStartPos;
		Chunk*			mCurrentChunk;
		Chunk*			mGhostRootChunk;
		String			mCurrentIndent;
		String			mCurrentLine;
		ReadChunk       mReadChunk;
		ReadEntry       mReadEntry;
		StrStream	mOutStream;
		StrStream	mInStream;
		StrStream	mInStream2;
		size_t			mNumNotFoundEntries;
	};

} // namespace GothOgre

#endif // GOTHOGRE_ZEN_ARCHIVE_IMPL_ASCII_H