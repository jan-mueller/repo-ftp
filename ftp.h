#ifndef _FTP_H_

#define _FTP_H_

class FtpServer{
	public:
		// CONSTRUCTOR / DESTRUCTOR

		FtpServer();
		~FtpServer();

		class UserEntry;
		class ClientEntry;

		friend class UserEntry;
		friend class ClientEntry;

	private:
		class EnumFileInfo;
		class CriticialSection;

	public:
		// START / STOP
		
		// Ask server for listening on port supplied by SetPort()
		// ulAddr: Address the Server will isten on
		// usPort: Port the Server will listen
		// return: true on success
		// 		  false on error  
		bool StartListening(unsigned long ulAddr, unsigned short int usPort);
		// Ask server for stop listening
		// return: true on success
		// 		  false on error
		bool StopListening();
		// Check if server is listening
		// return: true if Server is listening
		// 		  false otherwise
		bool IsListening()const{return bIsListening;}
		// Ask server for accepting clients
		// return: true on success
		// 		  false on error
		bool StartAccepting();
		// Check if server is accepting clients
		// return: true on success
		// 		  false on error
		bool IsAccepting()const{return bIsAccepting;}

		// CONFIG

		// Get TCP port on which the server is listening
		// return: Port number
		unsigned short GetListeningPort()const{return usListeningPort;}
		// Set portrange the server can use to send and receive data
		// usStart: the first port
		// uiLen: number of ports
		// return: true on success
		// 		  false on error  
		bool SetDataPortRange(unsigned short int usStart, unsigned short int uiLen);
		// Get portrange the server can use to send and receive data
		// usStart: Pointer to the first port
		// uiLen: Pointer to the number of ports
		// return: true on success
		// 		  false on error  
		bool GetDataPortRange(unsigned short int *usStart, unsigned short int *usLen);
		// Set the time in which a user has to login
		// ulSecond: timeout delay in seconds
		void SetNoLoginTimeout(unsigned long int ulSecond){ulNoLoginTimeout=ulSecond;}
		// Get the time in which a user has to login
		// return: timeout delay in seconds
		unsigned long int GetNoLoginTimeout()const{return ulNoLoginTimeout;}
		// Set the no transfer (list, download or upload) timeout
		// ulSecond timeout delay in seconds
		void SetNoTransferTimeout(unsigned long int ulSecond){ulNoTransferTimeout=ulSecond;}
		// Get the no transfer (list, download or upload) timeout
		// return: timeout delay in seconds
		unsigned long int GetNoTransferTimeout()const{return ulNoTransferTimeout;}
		// Set the delay the server will wait when checking for the client's pass
		// ulMilliSecond: the timeout delay in milliseconds
		void SetCheckPassDelay(unsigned int ulMilliSecond){uiCheckPassDelay=ulMilliSecond;}
		// Get the delay the server will wait when checking for the client's pass
		// return: the timeout delay in milliseconds
		unsigned int GetCheckPassDelay()const{return uiCheckPassDelay;}
		// Set the max allowed password tries per client
		// uiMaxPassTries: the max allowed password tries
		void SetMaxPasswordTries(unsigned int uiMaxPassTries){uiMaxPasswordTries=uiMaxPassTries;}
		// Get the max allowed password tries per client
		// return: the max allowed password tries per client
		unsigned int GetMaxPasswordTries()const{return uiMaxPasswordTries;}
		// Enable or disable server-to-server transfer
		// bEnable: true to enable, and false to disable
		void EnableFXP(bool bEnable){bEnableFXP=bEnable;}
		// Check if server-to-server transfer is enabled
		//	return: true on success
		// 		  false on error  
		bool IsFXPEnabled()const{return bEnableFXP;}
		// Set the size of the file transfer and directory listing buffer which
		// will be allocated for each client
		// uiSize: the transfer buffer size
		void SetTransferBufferSize(unsigned int uiSize){uiTransferBufferSize=uiSize;}
		// Get the size of the file transfer and directory listing buffer which
		// will be allocated for each client
		// return: the transfer buffer size
		unsigned int GetTransferBufferSize()const{return uiTransferBufferSize;}
		// Set the size of the file transfer and directory listing socket buffer which 
		// will be allocated for each client
		// uiSize: the transfer socket buffer size
		void SetTransferSocketBufferSize(unsigned int uiSize){uiTransferSocketBufferSize=uiSize;}

		// STATISTICS

		// Get number of clients connected to the server
		// return: number of clients
		unsigned int GetNbClient() const { return uiNumberOfClient; }
		// Get number of existing users
		// return: number of users
		unsigned int GetNbUser() const { return uiNumberOfUser; }

		// EVENTS

		// Enum the events that can be send to the events callback
		enum eEvents {
			// User events
			NEW_USER,
			DELETE_USER,
			// Client events
			NEW_CLIENT,
			DELETE_CLIENT,
			CLIENT_DISCONNECT,
			CLIENT_AUTH,
			CLIENT_UPLOAD,
			CLIENT_DOWNLOAD,
			CLIENT_LIST,
			CLIENT_CHANGE_DIR,
			RECVD_CMD_LINE,
			SEND_REPLY,
			TOO_MANY_PASS_TRIES,
			NO_LOGIN_TIMEOUT,
			NO_TRANSFER_TIMEOUT,
			CLIENT_SOCK_ERROR,
			CLIENT_SOFTWARE,
			// Server event
			START_LISTENING,
			STOP_LISTENING,
			START_ACCEPTING,
			STOP_ACCEPTING,
			MEM_ERROR,
			THREAD_ERROR,
		};


		typedef void (*OnServerEventCallback_t) ( int Event );
		typedef void (*OnUserEventCallback_t) ( int Event, FtpServer::UserEntry *pUser, void *pArg );
		typedef void (*OnClientEventCallback_t) ( int Event, FtpServer::ClientEntry *pClient, void *pArg );
		// Set the Server event callback
		// pCallback: the callback function
		void SetServerCallback(nServerEventCallback_t pCallback)
			{_OnServerEventCb=pCallback;}
		// Set the User event callback
		// pCallback: the callback function
		void SetUserCallback(OnUserEventCallback_t pCallback)
			{_OnUserEventCb=pCallback;}
		// Set the client event callback
		// pCallback: the callback function
		void SetClientCallback(OnClientEventCallback_t pCallback)
			{_OnClientEventCb=pCallback;}
		// call the server event callback
		// Event: the callback arguments
		void OnServerEventCb(int Event)
			{if(_OnServerEventCb) _OnServerEventCb(Even );}
		// call the user event callback
		// Event: the callback arguments
		// pUser: a pointer to the user class
		// pArg: a pointer to something that depends on Event
		void OnUserEventCb(int Event, FtpServer::UserEntry *pUser, void *pArg=NULL)
			{if(_OnUserEventCb)_OnUserEventCb(Event, pUser, pArg);}
		// call the client event callback
		// Event: the callback arguments
		// pClient: a pointer to the client class
		// pArg: a pointer to something that depends on Event
		void OnClientEventCb(int Event, FtpServer::ClientEntry *pClient, void *pArg=NULL)
			{if(_OnClientEventCb)_OnClientEventCb(Event, pClient, pArg);}
		
		// USER

		// Enumerate the different Privileges a User can get
		enum
		{
			READFILE=0x1,
			WRITEFILE=0x2,
			DELETEFILE=0x4,
			LIST=0x8,
			CREATEDIR=0x10,
			DELETEDIR=0x20
		};
		// Create a new User
		// pszLogin     the User Name
		// pszPass      the User Password, Can be NULL
		// pszStartDir  the User Start directory
		// return: on success a pointer to the newly created User
		//         on error NULL
		CUserEntry *AddUser(const char *pszLogin, const char *pszPass, const char *pszStartDir);
		// Delete a User, and by the way all the Clients connected to this User
		// return: true on success
		//         false on error
		bool DeleteUser(FtpServer::UserEntry *pUser);

	private:
		
		// EVENTS

		OnServerEventCallback_t _OnServerEventCb;
		OnUserEventCallback_t _OnUserEventCb;
		OnClientEventCallback_t _OnClientEventCb;

		// CLASS CriticialSection

		class CriticialSection{
			public:
				bool Initialize(){
					pthread_mutex_init(&m_CS, NULL);
					return true;
				}
				bool Enter(){
					pthread_mutex_lock(&m_CS);
					return true;
				}
				bool Leave(){
					pthread_mutex_unlock(&m_CS);
					return true;
				}
				bool Destroy(){
					pthread_mutex_destroy( &m_CS );
					return true;
				}
			private:
				pthread_mutex_t m_CS;
		}FtpServerLock;

		// USER

		enum{
			MaxLoginLen=16,
			MaxPasswordLen=16,
			MaxRootPathLen=MAX_PATH
		};

		class CCriticialSection UserListLock;
		class CUserEntry *pFirstUser, *pLastUser;
		// warning  MUST lock the UserListLock before calling this function
		CUserEntry *SearchUserFromLogin(const char *pszName);

		// CLIENT

		// Add a new Client.
		// return: on success a pointer to the new ClientEntry class
		//         on error NULL
		FtpServer::ClientEntry *AddClient(SOCKET Sock, struct sockaddr_in *Sin);

		class CriticialSection ClientListLock;
		class ClientEntry *pFirstClient, *pLastClient;

		// Network

		volatile SOCKET ListeningSock;

		struct{
			unsigned short int usLen, usStart;
		}DataPortRange;

		bool bIsListening;
		bool bIsAccepting;
		unsigned short int usListeningPort;

		pthread_t AcceptingThreadID;
		static void *StartAcceptingEx( void *pvParam );
		pthread_attr_t m_pattrServer;
		pthread_attr_t m_pattrClient;
		pthread_attr_t m_pattrTransfer;

		// FILE

		// Simplify a Path
		static bool SimplifyPath(char *pszPath);

		// STATISTIC

		unsigned int uiNumberOfUser;
		unsigned int uiNumberOfClient;

		// CONFIG

		unsigned int uiMaxPasswordTries;
		unsigned int uiCheckPassDelay;
		unsigned long int ulNoTransferTimeout, ulNoLoginTimeout;
		unsigned int uiTransferBufferSize, uiTransferSocketBufferSize;

		bool bEnableFXP;

};

// FtpServer::UserEntry CLASS
// brief FtpServer::UserEntry class
// One instance of this class will be allocated for each user.
class FtpServer::UserEntry
{
	public:
		UserEntry();
		~UserEntry(){}

		friend class FtpServer;
		friend class FtpServer::ClientEntry;
		// Set the Privileges of a User
		// ucPriv: the user's privileges separated by the bitwise inclusive binary operator "|"
		// return: true on success
		// 		  false on error
		bool SetPrivileges(unsigned char ucPriv);
		// Get a User's privileges
		// return: the user's privileges concatenated with the bitwise inclusive binary operator "|"
		unsigned char GetPrivileges()const{return ucPrivileges;}
		// Get the number of Clients logged-in as the User
		// return: the number of Clients
		unsigned int GetNumberOfClient()const{return uiNumberOfClient;}
		// Set the maximum number of Clients which can be logged in as the User at the same time
		// uiMax: the number of clients
		void SetMaxNumberOfClient(unsigned int uiMax){uiMaxNumberOfClient=uiMax;}
		// Get the maximum number of Clients which can be logged in as the User at the same time
		// return: the number of clients
		unsigned int GetMaxClient()const{return uiMaxNumberOfClient;}
		// Get a pointer to the User's Name
		// return: A pointer to the User's Name
		const char *GetLogin()const{return szLogin;}
		// Get a pointer to the User's Password
		// return: A pointer to the User's Password
		const char *GetPassword()const{return szPassword;}
		// Get a pointer to the User's Start Directory
		// return: A pointer to the User's Start Directory
		const char *GetStartDirectory()const{return szStartDirectory;}
		// Set the supported Extra-Commands of a User
		// dExtraCmd: the user's Extra-Commands concatenated with the bitwise inclusive binary operator "|"
		// return: true on success
		//         false on error
		bool SetExtraCommand(unsigned char dExtraCmd);
		// * Get the supported Extra-Commands of a User.
		// * @return  The user's Extra-Commands concatenated with the bitwise inclusive binary operator "|".
		unsigned char GetExtraCommand()const{return ucExtraCommand;}

	private:

		unsigned char ucExtraCommand;
		class UserEntry *pPrevUser, *pNextUser;
		bool bDelete;
		bool bIsEnabled;
		FtpServer *pFtpServer;
		unsigned char ucPrivileges;
		char szLogin[ MaxLoginLen + 1 ];
		char szPassword[ MaxPasswordLen + 1 ];
		char szStartDirectory[ MaxRootPathLen + 1 ];
		unsigned int uiNumberOfClient, uiMaxNumberOfClient;
};


#endif
