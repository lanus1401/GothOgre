#ifndef GOTHOGRE_ZEN_ARCHIVE_H
#define GOTHOGRE_ZEN_ARCHIVE_H

#include "GothOgre_ZenObject.h"
#include "GothOgre_DataStreamEx.h"
#include "GothOgre_EnumIO.h"
#include "GothOgre_FlagSet.h"


namespace GothOgre
{
	class ZenArchiveImpl;

	class ZenArchiveType
	{
	public:
		enum Enum
		{
			// �������� �����: ����������� ������ � ������������ �������� ������, �� ������������:
			// ����� � ���� �������� ������ �� �������� � �������, �.�. ��������� ���������������
			// ������ ������� ����������� ������ ������.
			// �����: zArchiverBinary.
			// �������������: SAV-�����, MeshAndBsp-������ ������ ZEN-�����.
			BINARY,

			// ASCII-�����: ������� ������ � ��������� �������� ������, ����������:
			// ������ �������� ������ � ������� � ������, � ��������� ����,
			// ���� ���������, �� ���� ��� �������� ����������� �����.
			// �����: zArchiverASCII.
			// �������������: ZEN(ascii).
			ASCII,

			// ���������� �������� �����: ������� ������ � ������� �������� ������:
			// ������ �������� � �������� ����, �� � ������� �� zARCMODE_BINARY, 
			// ����� � ���� �������� �������� � ������.
			// �����: zArchiverBinSafe.
			// �������������: SAV-�����, ZEN(binary safe), ou.bin.
			BIN_SAFE
		};

		ZenArchiveType(int _value = ASCII) : mValue(Enum(_value)) {}
		operator int() const {return mValue;}
		GOTHOGRE_DECLARE_ENUM_IO( ZenArchiveType )
	private:
		Enum mValue;
	};

	//------------------------------------------------------------------------
	struct ZenArchiveFlags : public FlagSet
	{
		enum Enum
		{
			DEFAULT      = 0x00,
			SAVE_GAME    = 0x01,
			NO_DATE      = 0x02,
			NO_USER_INFO = 0x04,
			NO_CODE_PAGE = 0x08,
			NO_LOG       = 0x10
		};
		ZenArchiveFlags(int _val = DEFAULT) : FlagSet(_val) {}
	};

	//------------------------------------------------------------------------
	// ����������� ������� ����� ������
	class GOTHOGRE_EXPORT ZenArchive
	{
	public:
		class Vec3
		{
		public:
			Vec3(const Vec3& _src) 
			{
				memcpy(mData, _src.mData, sizeof(mData));
			}

			Vec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f)
			{
				mData[0] = _x; mData[1] = _y; mData[2] = _z;
			}

			Vec3(const float* _data) 
			{
				memcpy(mData, _data, sizeof(mData));
			}

			Vec3(const Vector3& _ogreVector3)
			{
				mData[0]   = (float) _ogreVector3.x;
				mData[1] = (float) _ogreVector3.y;
				mData[2]  = (float) _ogreVector3.z;
			}

			const Vec3& operator =(const Vec3& _src) 
			{
				memcpy(mData, _src.mData, sizeof(mData)); 
				return *this;
			}

			float getX() const {return mData[0];}
			float getY() const {return mData[1];}
			float getZ() const {return mData[2];}

			void setX(float _x) {mData[0] = _x;}
			void setY(float _y) {mData[1] = _y;}
			void setZ(float _z) {mData[2] = _z;}

			static const Vec3 ZERO;

			Vector3 toVector3() const
			{
				Vector3 ogreVector3;
				ogreVector3.x = (Real) mData[0];
				ogreVector3.y = (Real) mData[1];
				ogreVector3.z = (Real) mData[2];
				return ogreVector3;
			}

		private:
			float mData[3];
		};

	public:
		class Color
		{
		public:
			Color(const Color& _src) 
			{
				memcpy(mData, _src.mData, sizeof(mData));
			}

			Color(uchar _red = 255, uchar _green = 255, uchar _blue = 255, uchar _alpha = 255)
			{
				mData[RED] = _red; mData[BLUE] = _blue; mData[GREEN] = _green; mData[ALPHA] = _alpha;
			}

			Color(const uchar* _data) 
			{
				memcpy(mData, _data, sizeof(mData));
			}

			Color(const ColourValue& _ogreColour)
			{
				mData[RED]   = (uchar) Math::IFloor(_ogreColour.r * 255);
				mData[GREEN] = (uchar) Math::IFloor(_ogreColour.g * 255);
				mData[BLUE]  = (uchar) Math::IFloor(_ogreColour.b * 255);
				mData[ALPHA] = (uchar) Math::IFloor(_ogreColour.a * 255);
			}

			const Color& operator =(const Color& _src) 
			{
				memcpy(mData, _src.mData, sizeof(mData)); 
				return *this;
			}

			enum
			{
				BLUE  = 0,
				GREEN = 1,
				RED   = 2,
				ALPHA = 3
			};

			uchar getRed() const {return mData[RED];}
			uchar getGreen() const {return mData[GREEN];}
			uchar getBlue() const {return mData[BLUE];}
			uchar getAlpha() const {return mData[ALPHA];}

			void setRed(uchar _red) {mData[RED] = _red;}
			void setGreen(uchar _green) {mData[GREEN] = _green;}
			void setBlue(uchar _blue) {mData[BLUE] = _blue;}
			void setAlpha(uchar _alpha) {mData[ALPHA] = _alpha;}

			static const Color BLACK;

			ColourValue toColourValue() const
			{
				ColourValue ogreColour;
				ogreColour.r = mData[RED]   / Real(255.f);
				ogreColour.g = mData[GREEN] / Real(255.f);
				ogreColour.b = mData[BLUE]  / Real(255.f);
				ogreColour.a = mData[ALPHA] / Real(255.f);
				return ogreColour;
			}

		private:
			uchar mData[4];
		};

	public:
		/**  */
		class Chunk
		{
		public:
			virtual ~Chunk() {}
			Chunk* getParent() const {return mParent;}
			const String& getChunkName() const {return mChunkName;}
			const String& getChunkType() const {return mChunkType;}
			ushort getObjectVersion() const {return mObjectVersion;}
			ulong getObjectIndex() const {return mObjectIndex;}
			size_t getChunkPos() const {return mChunkPos;}
			size_t getDataPos() const {return mDataPos;}
			ZenObjectPtr getObject() const {return mObject;}

		protected:
			Chunk() {mParent = nullptr; mObjectVersion = 0; mObjectIndex = 0; mChunkPos = 0;}

		protected:
			friend class ZenArchive;
			Chunk*			mParent;
			String			mChunkName;
			String			mChunkType;
			ushort			mObjectVersion;
			ulong			mObjectIndex;
			size_t			mChunkPos;
			size_t          mDataPos;
			ZenObjectPtr	mObject;
		};

	public:
		typedef map<ZenObjectPtr, ulong>::type  ObjectWriteMap; // index by object
		typedef vector<ZenObjectPtr>::type      ObjectReadList;

		static const String CHUNKNAME_EMPTY;  // "%" (percent sign)
		static const String CHUNKTYPE_EMPTY;  // "%" (percent sign)
		static const String CHUNKTYPE_OBJREF; // "�" (section sign)

	public:
		// �����������
		ZenArchive();
		
		// ���������� - ��������� �����
		~ZenArchive();

		// ������� �����
		void readHeader(const String& _filename, const String& _resourceGroup, ZenArchiveFlags _flags = ZenArchiveFlags::DEFAULT);
		void readHeader(const DataStreamExPtr& _dataStream, ZenArchiveFlags _flags = ZenArchiveFlags::DEFAULT);
		void readFooter();

		void writeHeader(const String& _filename, const String& _resourceGroup, ZenArchiveType _type, ZenArchiveFlags _flags = ZenArchiveFlags::DEFAULT);
		void writeHeader(const DataStreamExPtr& _dataStream, ZenArchiveType _type, ZenArchiveFlags _flags = ZenArchiveFlags::DEFAULT);
		void writeFooter();

		const String& getName() const {return mName;}
		const String& getBaseName() const {return mBaseName;}
		bool isWriting() const {return mWriting;}
		DataStreamExPtr getDataStream() const {return mDataStream;}
		ZenArchiveType  getType() const {return mType;}
		ZenArchiveFlags getFlags() const {return mFlags;}
		size_t getNumObjects() const {return mWriting ? mObjectWriteMap.size() : mObjectReadList.size();}

	public:
		// �������� � ����� �������� - ����� ����� (4 �����)
		void writeInt(const String& _entryName, int _value);	

		// �������� � ����� �������� - ����
		void writeByte(const String& _entryName, unsigned char _value);
		
		// �������� � ����� �������� - ����� (2 �����)
		void writeWord(const String& _entryName, unsigned short _value);

		// �������� � ����� �������� - ������������ �������� (4 �����)
		void writeFloat(const String& _entryName, float _value);
		void writeReal(const String& _entryName, Real _value);

		// �������� � ����� �������� - ���������� ��������
		void writeBool(const String& _entryName, bool _value);

		// �������� � ����� �������� - ������
		void writeString(const String& _entryName, const String& _value);

		// �������� � ����� �������� - ������
		void writeVec3(const String& _entryName, const Vec3& _value);
		void writeVector3(const String& _entryName, const Vector3& _value);

		// �������� � ����� �������� - ����
		void writeColor(const String& _entryName, const Color& _value);
		void writeColourValue(const String& _entryName, const ColourValue& _value);
		
		// �������� � ����� �������� - ������ ����
		void writeRaw(const String& _entryName, const void* _rawData, size_t _sizeInBytes);

		// �������� � ����� �������� - ������ ������������ �����
		void writeRawFloat(const String& _entryName, const float* _rawData, size_t _sizeInBytes);
		void writeRawReal(const String& _entryName, const Real* _rawData, size_t _sizeInBytes);
		void writeMatrix3(const String& _entryName, const Matrix3& _matrix);

		// �������� � ����� �������� - ������������;
		// ������ �������� ��������� ����� �������� ������������,
		// ����� ����� � �������.
		void writeEnum(const String& _entryName, int _value);

		// ������ ������ ����� � �����.
		Chunk* writeChunkBegin(const String& _chunkName = StringUtil::BLANK, const String& _chunkType = StringUtil::BLANK, ushort _objectVersion = 0, ulong _objectIndex = 0);
		
		// ��������� ������ ����� � �����.
		void writeChunkEnd(Chunk* _chunk);

		// �������� � ����� ������, ����������� �� zCObject;
		// ������ ������������ � ����� � ���� � ��������� ������.
		void writeObject(const String& _chunkName, ZenObjectPtr _zenObject);

		// �������� � ����� ������, ����������� �� zCObject;
		// ������ ������������ � ����� � ���� ����������� �����.
		void writeObject(ZenObjectPtr _zenObject);

	public:
		// ��������� �� ������ �������� - ����� ����� (4 �����)
		int readInt(const String& _entryName, int _defaultValue = 0);

		// ��������� �� ������ �������� - ����
		uchar readByte(const String& _entryName, uchar _defaultValue = 0);

		// ��������� �� ������ �������� - ����� (2 �����)
		ushort readWord(const String& _entryName, ushort _defaultValue = 0);

		// ��������� �� ������ �������� - ������������ ����� (4 �����)
		float readFloat(const String& _entryName, float _defaultValue = 0);
		Real readReal(const String& _entryName, Real _defaultValue = 0);

		// ��������� �� ������ �������� - ���������� ��������
		bool readBool(const String& _entryName, bool _defaultValue = false);

		// ��������� �� ������ �������� - ������
		String readString(const String& _entryName, const String& _defaultValue = StringUtil::BLANK);

		// ��������� �� ������ �������� - ������
		Vec3 readVec3(const String& _entryName, const Vec3& _defaultValue = Vec3::ZERO);
		Vector3 readVector3(const String& _entryName, const Vector3& _defaultValue = Vector3::ZERO);

		// ��������� �� ������ �������� - ����
		Color readColor(const String& _entryName, const Color& _defaultValue = Color::BLACK);
		ColourValue readColourValue(const String& _entryName, const ColourValue& _defaultValue = ColourValue::Black);

		// ��������� �� ������ �������� - ������������
		int readEnum(const String& _entryName, int _defaultValue = 0);

		// ��������� �� ������ �������� - ������ ����
		size_t readRaw(const String& _entryName, void* _rawData, size_t _sizeInBytes);

		// ��������� �� ������ �������� - ������ ������������ �����
		size_t readRawFloat(const String& _entryName, float* _rawData, size_t _sizeInBytes);
		size_t readRawReal(const String& _entryName, Real* _rawData, size_t _sizeInBytes);
		Matrix3 readMatrix3(const String& _entryName, const Matrix3& _defaultValue = Matrix3::ZERO);

		// ��������� �� ������ ���� � ��������� ������.
		// ���� ���� � ��������� ������ �� ������, ������������ FALSE.
		Chunk* readChunkBegin(const String& _chunkName);

		Chunk* readChunkBegin();

		// ��������� ����� ����� �� ������, �.�. ���������� ��� 
		// �� ����� �������� ����� ������������.
		void readChunkEnd(Chunk* _chunk);		

		// ��������� �� ������ ������, ����������� �� zCObject � ��������� ������ �����.
		// ������������ ��������� �� ����������� ������ ��� NULL � ������ ������.
		// ���� ������ �������� �� NULL, �� ��� ������� �� �����
		// ��������� ����� ������, � ���������� ��������� � ������ ��������� ��� ���������.
		ZenObjectPtr readObject(const String& _chunkName);

		// ��������� �� ������ ������, ����������� �� zCObject,
		// �.�. ��� ����� �� �������, ������� ����� ������ ������ ��������� ������ �� ������.
		// ������������ ��������� �� ����������� ������ ��� NULL � ������ ������.
		// ���� ������ �������� �� NULL, �� ��� ������� �� �����
		// ��������� ����� ������, � ���������� ��������� � ������ ��������� ��� ���������.
		ZenObjectPtr readObject();

		// ���������� ������, ����������� �� zCObject, �� ����� ���
		void skipObject();

		// �������� ������� ����
		Chunk* getCurrentChunk() const;

	private:
		void makeBaseName();
		void readHeader();
		void writeHeader();
		void processFooter();
		void endCurrentChunk();
		void endAllChunks();
		static String getUserName();
		Chunk* _readChunkBegin(const String& _chunkName);
		ZenObjectPtr _readObject(const String& _chunkName);

	private:
		String					mName;
		String					mBaseName;
		DataStreamExPtr			mDataStream;
		bool					mWriting;
		ZenArchiveType			mType;
		ZenArchiveFlags			mFlags;
		vector<float>::type     mFloatVector;
		ZenArchiveImpl*			mImpl;
		ObjectWriteMap			mObjectWriteMap;
		ObjectReadList			mObjectReadList;
		Chunk*					mCurrentChunk;
	};

} // namespace GothOgre

#endif // GOTHOGRE_ZEN_ARCHIVE_H