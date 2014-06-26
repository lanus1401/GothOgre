#ifndef VDFS_ARCHIVE_H
#define VDFS_ARCHIVE_H


// ���� Vdfs-����� ����������� �������� ����� ������
class VdfsArchive : public Ogre::Archive 
{
public:
	// �����������, ��������������� ���������� �� ������,
	// ���� ���������� VdfsArchiveFactory
	VdfsArchive( const String& name, const String& archType );
	~VdfsArchive();

	// ���������������� � ��������, ����� ���� �����
	bool isCaseSensitive() const { return false; }

	// ��������� �����
	void load();
	
	// ��������� �����
	void unload();

	// ������� ���� � ������
	DataStreamPtr open(const String& filename) const;

	// �������� ������ ������ � ������
	StringVectorPtr list(bool recursive = true, bool dirs = false);

	// �������� ������ ������ � ������ � �������������� �����������
	FileInfoListPtr listFileInfo(bool recursive = true, bool dirs = false);

	// ����� ���� � ������
	StringVectorPtr find(const String& pattern, bool recursive = true,
		bool dirs = false);

	// ����� ���� � ������ � �������� �������������� ����������
	FileInfoListPtr findFileInfo(const String& pattern, bool recursive = true,
		bool dirs = false);

	// ��������� ������������� �����
	bool exists(const String& filename);

	// �������� ���� ���������� ��������� �����
	time_t getModifiedTime(const String& filename);
};


// ������� VDFS-������� - ���������� � ������������ �����
class VdfsArchiveFactory : public ArchiveFactory
{
public:
	virtual ~VdfsArchiveFactory();
	const String& getType(void) const;
	Archive *createInstance( const String& name );
	void destroyInstance( Archive* arch);
};


// ����� ������ �� ��������� ����� � VDFS-������
class VdfsDataStream : public DataStream
{
public:
	VdfsDataStream(...);
	~VdfsDataStream();
	size_t read(void* buf, size_t count);
	void skip(long count);
	void seek( size_t pos );
	size_t tell(void) const;
	bool eof(void) const;
	void close(void);
};


#endif // VDFS_ARCHIVE_H