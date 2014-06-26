



	class Sound : public MovableObject
	{

	public:
		void setSound2D(const String& _filename, const String& _resourceGroup);

		void setSound2D(const String& _filename);
		void setSound3D(const String& _filename);
		void setMusic2D(const String& _filename);
		void setMusic3D(const String& _filename);

		void play(bool _3D);
		void stop();

		void setVolume(Real _volume);
		void setMaxDistance(Real _radius);
	};

	class SoundSystem : public Singleton<SoundSystem>
	{
		Sound* createSound();

		void setListener(MovableObject* _listener);
	};

	//-----------------------------------------------------------------------
	/** SoundChannel - Entity which is used to display Bsp. */
	class GOTHOGRE_EXPORT SoundChannel : public MovableObject
	{
	public:
		// ��� ��������� �����
		enum ChannelType
		{
			// ���������� (����������)
			CHANNEL_2D,

			// ���������� (����������������)
			CHANNEL_3D
		};

		// ������� ������ ��������� �����
		enum ChannelStatus
		{
			// ������������ ����������� (������ �� ���������)
			STOPPED,

			// ������������ ���������� �� �����
			PAUSED,

			// �������������
			PLAYING,
			
			// ������������� ���-�� ������ �� ���������, 
			// ��� ��� ���� �� ������
			PLAYING_FAR_AWAY
		};

		// �������� �� ���������� ������������ �����
		enum EndAction
		{
			// ������ �� ������; ���� ����������� �� ����� � ���
			NONE,

			// ������� �������� ����� ����� ���������� ������������
			// ������� ��� ��������� ������, ������������ ��-�� �������
			// �������, ���� ��������� ������ ����� ��� �����
			DELETE_CHANNEL,
			
			// ��������� ���� �����
			LOOP_BACK,

			// ��������� ��������� �����, � ����� ��������� ���� �����
			DELAYED_LOOP_BACK
		};

		// �������� ��������� �� ������, ���������� ����
		const SoundPtr& getSound() const {return mSound;}

		// ��������� ������������ 2D �����
		void play2D()
		{
			stop();
			mChannelType = CHANNEL_2D;
			mChannelStatus = PLAYING_FAR_AWAY;
		}

		// ��������� ������������ 3D �����
		void play3D()
		{
			stop();
			mChannelType = CHANNEL_3D;
			mChannelStatus = PLAYING_FAR_AWAY;
		}

		void _play2D()
		{
			mChannelData = mSound->play2D();
			mChannelData->setVolume(mVolume);
			mChannelStatus = PLAYING;
		}

		void _play3D()
		{
			mChannelData = mSound->play3D();
			mChannelData->setVolume(mVolume);
			mChannelData->setRadius(mRadius);
			mChannelData->setPosition(getParentNode()->getDerivedPosition());
			mChannelStatus = PLAYING;
		}

		// ���������� ������������
		void stop()
		{
			if(mChannelData)
			{
				delete mChannelData;
				mChannelData = nullptr;
			}
			mChannelStatus = STOPPED;
		}

		// ��������� �� �����
		void pause(bool _pause = true)
		{
			if(mChannelData)
				mChannelData->pause(_pause);
			if(mChannelStatus == PLAYING)
				mChannelStatus = PAUSED;
		}

		// ����� � �����
		void unpause() {pause(false);}

		// ���������, ���������� �� ������������ �� �����
		bool isPaused() const {return getChannelStatus() == PAUSED;}

		// �������� ����� ����� � ��������
		Real getPlayDuration() const
		{
			if(mChannelData)
				return mChannelData->getSoundData()->getPlayDuration();
			return 0;
		}

		// �������� ������� ������� � �������� �� ������ �����
		Real getPlayPosition() const
		{
			if(mChannelData)
				return mChannelData->getPlayPosition();
			return 0;
		}

		// �������� ��� ��������� �����
		ChannelType getChannelType() {return mChannelType;}

		// �������� ������� ������ ��������� �����
		ChannelStatus getChannelStatus() {return mChannelStatus;}

		// ���������� ��������, ������� ������ ���� ��������� 
		// �� ���������� ������������
		void setEndAction(EndAction _ea)
		{
			mEndAction = _ea;
		}

		// �������� ��������, ������� ������ ���� ��������� 
		// �� ���������� ������������
		EndAction getEndAction() const {return mEndAction;}

		// ���������� ��������� �����, � ��������� �� 0 �� 1
		void setVolume(Real _volume)
		{
			mVolume = _volume;
			if(mChannelData)
				mChannelData->setVolume(_volume);
		}

		// �������� ��������� �����, � ��������� �� 0 �� 1
		Real getVolume() {return mVolume;}

		// ���������� ������������ ���������� �� ��������� �����,
		// �� ������� ���� ��� ������ (������ ��� 3D �����)
		void setBoundingRadius(Real _radius)
		{
			mBoundingRadius = _radius;
			if(mChannelData)
				mChannelData->setBoundingRadius(_radius);
		}

		// �������� ������������ ���������� �� ��������� �����,
		// �� ������� ���� ��� ������ (������ ��� 3D �����)
		Real getBoundingRadius() const {return mBoundingRadius;}

		// ���������� �������������� ��������������, ������ �������� 
		// ������������� ����, ��������� ����� �� ������� �� ��������� 
		// ��������� ������ ��������������� (������ ��� 2D �����)
		void setBoundingBox(const AxisAlignedBox& _box)
		{
			mBoundingBox = _box;
		}

		// �������� �������������� ��������������, ������ �������� 
		// ������������� ����, ��������� ����� �� ������� �� ��������� 
		// ��������� ������ ��������������� (������ ��� 2D �����)
		const AxisAlignedBox& getBoundingBox() const {return mBoundingBox;}

		// ���������� ����������� ��������, � �������� (��. �������� DelayedLoopBack)
		void setMinDelay(Real _minDelay)
		{
			mMinDelay = _minDelay;
		}

		// �������� ����������� ��������, � �������� (��. �������� DelayedLoopBack)
		Real getMinDelay() const {return mMinDelay;}

		// ���������� ������������ ��������, � �������� (��. �������� DelayedLoopBack)
		void setMaxDelay(Real _maxDelay)
		{
			mMaxDelay = _maxDelay;
		}

		// �������� ������������ ��������, � �������� (��. �������� DelayedLoopBack)
		Real getMaxDelay() const {return mMaxDelay;}

	public:
		// Returns the type name of this object. 
		const String& getMovableType() const;

		// Get the 'type flags' for this MovableObject.
		// ���������� 0, �.�. �������� ����� � �������� �� ���������,
		// � � ����� ������������ ������� �� ���������.
		uint32 getTypeFlags() const {return 0;}
		
		// Internal method by which the movable object must 
		// add Renderable subclass instances to the rendering queue.
		// ������� ������ �� ������, �������� ����� ����� �� ��������������.
		void _updateRenderQueue(RenderQueue* queue) {}

	private:
		SoundChannel()
		{
			mChannelType = CHANNEL_2D;
			mChannelStatus = STOPPED;
			mEndAction = NONE;
		}

		SoundChannel(const String& _name, const SoundPtr& _sound);

	private:
		SoundPtr                mSound;
		SoundData::ChannelData*  mChannelData;
		ChannelType              mChannelType;
		ChannelStatus            mChannelStatus;
		EndAction               mEndAction;
		Real                    mBoundingRadius;
		AxisAlignedBox          mBoundingBox;
		Real                    mVolume;
		Real                    mMinDelay;
		Real                    mMaxDelay;
	};

	class GOTHOGRE_EXPORT SoundChannelFactory : public MovableObjectFactory
	{
	public:
		SoundChannelFactory();
		~SoundChannelFactory();
		bool requestTypeFlags() const;
		const String& getType() const;
		static String FACTORY_TYPE_NAME;
	};

	class GOTHOGRE_EXPORT SoundListener : public MovableObject
	{

	};

	class SoundData
	{
	public:
		class ChannelData
		{
		public:
			// ����������� - �������� ������������
			ChannelData();

			// ���������� - ��������� ������������, 
			// ���� ��� ��� �� �����������
			virtual ~ChannelData();

			// ��������� �� ����� ��� ����� � �����
			virtual void pause(bool _pause) = 0;

			// ��������� ����
			virtual void setLooped(bool _looped) = 0;
			
			// ���������, ������������� �� ���� ���
			virtual bool isPlaying() const = 0;
			
			// �������� ������� �� ������ ����� � ��������
			virtual Real getPlayPosition() const = 0;

			// ���������� ��������� �����, �� 0 �� 1
			virtual void setVolume(Real _volume) = 0;
			
			// ���������� ������������ ���������� �� ���������,
			// �� ��������� �������� ���� �� ������
			virtual void setRadius(Real _radius) = 0;

			// ���������� ������� ��������� �����
			virtual void setPosition(const Vector3& _position);
		};

	public:
		SoundData();
		virtual ~SoundData();

		virtual ChannelData* play2D() = 0;
		virtual ChannelData* play3D() = 0;
		virtual Real getPlayDuration() const = 0;
	};