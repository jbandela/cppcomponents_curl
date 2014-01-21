namespace cppcomponents_libcurl_libuv{


	// Options copied from curl.h and placed in namespace
	namespace Constants{

		namespace Errors{
			typedef enum {
				CURLE_OK = 0,
				CURLE_UNSUPPORTED_PROTOCOL = -1,    /* 1 */
				CURLE_FAILED_INIT = -2,             /* 2 */
				CURLE_URL_MALFORMAT = -3,           /* 3 */
				CURLE_NOT_BUILT_IN = -4,            /* 4 */

				CURLE_COULDNT_RESOLVE_PROXY = -5,   /* 5 */
				CURLE_COULDNT_RESOLVE_HOST = -6,    /* 6 */
				CURLE_COULDNT_CONNECT = -7,         /* 7 */
				CURLE_FTP_WEIRD_SERVER_REPLY = -8,  /* 8 */
				CURLE_REMOTE_ACCESS_DENIED = -9,    /* 9  */
				CURLE_FTP_ACCEPT_FAILED = -10,       /* 10 */
				CURLE_FTP_WEIRD_PASS_REPLY = -11,    /* 11 */
				CURLE_FTP_ACCEPT_TIMEOUT = -12,      /* 12 */
				CURLE_FTP_WEIRD_PASV_REPLY = -13,    /* 13 */
				CURLE_FTP_WEIRD_227_FORMAT = -14,    /* 14 */
				CURLE_FTP_CANT_GET_HOST = -15,       /* 15 */
				CURLE_OBSOLETE16 = -16,              /* 16 - NOT USED */
				CURLE_FTP_COULDNT_SET_TYPE = -17,    /* 17 */
				CURLE_PARTIAL_FILE = -18,            /* 18 */
				CURLE_FTP_COULDNT_RETR_FILE = -19,   /* 19 */
				CURLE_OBSOLETE20 = -20,              /* 20 - NOT USED */
				CURLE_QUOTE_ERROR = -21,             /* 21 - quote command failure */
				CURLE_HTTP_RETURNED_ERROR = -22,     /* 22 */
				CURLE_WRITE_ERROR = -23,             /* 23 */
				CURLE_OBSOLETE24 = -24,              /* 24 - NOT USED */
				CURLE_UPLOAD_FAILED = -25,           /* 25 - failed upload "command" */
				CURLE_READ_ERROR = -26,              /* 26 - couldn't open/read from file */
				CURLE_OUT_OF_MEMORY = -27,           /* 27 */
				/* Note: CURLE_OUT_OF_MEMORY may sometimes indicate a conversion error
				instead of a memory allocation error if CURL_DOES_CONVERSIONS
				is defined
				*/
				CURLE_OPERATION_TIMEDOUT = -28,      /* 28 - the timeout time was reached */
				CURLE_OBSOLETE29 = -29,              /* 29 - NOT USED */
				CURLE_FTP_PORT_FAILED = -30,         /* 30 - FTP PORT operation failed */
				CURLE_FTP_COULDNT_USE_REST = -31,    /* 31 - the REST command failed */
				CURLE_OBSOLETE32 = -32,              /* 32 - NOT USED */
				CURLE_RANGE_ERROR = -33,             /* 33 - RANGE "command" didn't work */
				CURLE_HTTP_POST_ERROR = -34,         /* 34 */
				CURLE_SSL_CONNECT_ERROR = -35,       /* 35 - wrong when connecting with SSL */
				CURLE_BAD_DOWNLOAD_RESUME = -36,     /* 36 - couldn't resume download */
				CURLE_FILE_COULDNT_READ_FILE = -37,  /* 37 */
				CURLE_LDAP_CANNOT_BIND = -38,        /* 38 */
				CURLE_LDAP_SEARCH_FAILED = -39,      /* 39 */
				CURLE_OBSOLETE40 = -40,              /* 40 - NOT USED */
				CURLE_FUNCTION_NOT_FOUND = -41,      /* 41 */
				CURLE_ABORTED_BY_CALLBACK = -42,     /* 42 */
				CURLE_BAD_FUNCTION_ARGUMENT = -43,   /* 43 */
				CURLE_OBSOLETE44 = -44,              /* 44 - NOT USED */
				CURLE_INTERFACE_FAILED = -45,        /* 45 - CURLOPT_INTERFACE failed */
				CURLE_OBSOLETE46 = -46,              /* 46 - NOT USED */
				CURLE_TOO_MANY_REDIRECTS = -47,     /* 47 - catch endless re-direct loops */
				CURLE_UNKNOWN_OPTION = -48,          /* 48 - User specified an unknown option */
				CURLE_TELNET_OPTION_SYNTAX = -49,   /* 49 - Malformed telnet option */
				CURLE_OBSOLETE50 = -50,              /* 50 - NOT USED */
				CURLE_PEER_FAILED_VERIFICATION = -51, /* 51 */
				CURLE_GOT_NOTHING = -52,             /* 52 - when this is a specific error */
				CURLE_SSL_ENGINE_NOTFOUND = -53,     /* 53 - SSL crypto engine not found */
				CURLE_SSL_ENGINE_SETFAILED = -54,    /* 54 */
				CURLE_SEND_ERROR = -55,              /* 55 - failed sending network data */
				CURLE_RECV_ERROR = -56,              /* 56 - failure in receiving network data */
				CURLE_OBSOLETE57 = -57,              /* 57 - NOT IN USE */
				CURLE_SSL_CERTPROBLEM = -58,         /* 58 - problem with the local certificate */
				CURLE_SSL_CIPHER = -59,              /* 59 - couldn't use specified cipher */
				CURLE_SSL_CACERT = -60,              /* 60 - problem with the CA cert (path?) */
				CURLE_BAD_CONTENT_ENCODING = -61,    /* 61 - Unrecognized/bad encoding */
				CURLE_LDAP_INVALID_URL = -62,        /* 62 - Invalid LDAP URL */
				CURLE_FILESIZE_EXCEEDED = -63,       /* 63 - Maximum file size exceeded */
				CURLE_USE_SSL_FAILED = -64,          /* 64 - Requested FTP SSL level failed */
				CURLE_SEND_FAIL_REWIND = -65,        /* 65  */
				CURLE_SSL_ENGINE_INITFAILED = -66,   /* 66 - failed to initialise ENGINE */
				CURLE_LOGIN_DENIED = -67,            /* 67 */
				CURLE_TFTP_NOTFOUND = -68,           /* 68 - file not found on server */
				CURLE_TFTP_PERM = -69,               /* 69 - permission problem on server */
				CURLE_REMOTE_DISK_FULL = -70,        /* 70 - out of disk space on server */
				CURLE_TFTP_ILLEGAL = -71,            /* 71 - Illegal TFTP operation */
				CURLE_TFTP_UNKNOWNID = -72,          /* 72 - Unknown transfer ID */
				CURLE_REMOTE_FILE_EXISTS = -73,      /* 73 - File already exists */
				CURLE_TFTP_NOSUCHUSER = -74,         /* 74 - No such user */
				CURLE_CONV_FAILED = -75,             /* 75 - conversion failed */
				CURLE_CONV_REQD = -76,               /* 76 */
				CURLE_SSL_CACERT_BADFILE = -77,      /* 77  */
				CURLE_REMOTE_FILE_NOT_FOUND = -78,   /* 78 - remote file not found */
				CURLE_SSH = -79,                     /* 79 */

				CURLE_SSL_SHUTDOWN_FAILED = -80,     /* 80  */
				CURLE_AGAIN = -81,                   /* 81  */
				CURLE_SSL_CRL_BADFILE = -82,         /* 82*/
				CURLE_SSL_ISSUER_ERROR = -83,        /* 83 */
				CURLE_FTP_PRET_FAILED = -84,         /* 84 - a PRET command failed */
				CURLE_RTSP_CSEQ_ERROR = -85,         /* 85 - mismatch of RTSP CSeq numbers */
				CURLE_RTSP_SESSION_ERROR = -86,      /* 86 - mismatch of RTSP Session Ids */
				CURLE_FTP_BAD_FILE_LIST = -87,       /* 87 - unable to parse FTP file list */
				CURLE_CHUNK_FAILED = -88,            /* 88 - chunk callback reported error */
				CURLE_NO_CONNECTION_AVAILABLE = -89, /* 89 */
				CURL_LAST = -90/* never use! */
			};

		}

		namespace Options{

#define CPPCOMPONENTS_LIBCURL_LIBUV_CURLOPTTYPE_LONG          0
#define CPPCOMPONENTS_LIBCURL_LIBUV_CURLOPTTYPE_OBJECTPOINT   10000
#define CPPCOMPONENTS_LIBCURL_LIBUV_CURLOPTTYPE_FUNCTIONPOINT 20000
#define CPPCOMPONENTS_LIBCURL_LIBUV_CURLOPTTYPE_OFF_T         30000

			/* name is uppercase CURLOPT_<name>,
			type is one of the defined CURLOPTTYPE_<type>
			number is unique identifier */


#define CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(na,t,nu) CURLOPT_ ## na = CPPCOMPONENTS_LIBCURL_LIBUV_CURLOPTTYPE_ ## t + nu


			/*
			* This macro-mania below setups the CURLOPT_[what] enum, to be used with
			* curl_easy_setopt(). The first argument in the CPPCOMPONENTS_LIBCURL_LIBUV_CINIT() macro is the [what]
			* word.
			*/

			 enum {
				/* This is the FILE * or void * the regular output should be written to. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FILE, OBJECTPOINT, 1),

				/* The full URL to get/put */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(URL, OBJECTPOINT, 2),

				/* Port number to connect to, if other than default. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PORT, LONG, 3),

				/* Name of proxy to use. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROXY, OBJECTPOINT, 4),

				/* "name:password" to use when fetching. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(USERPWD, OBJECTPOINT, 5),

				/* "name:password" to use with proxy. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROXYUSERPWD, OBJECTPOINT, 6),

				/* Range to get, specified as an ASCII string. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RANGE, OBJECTPOINT, 7),

				/* not used */

				/* Specified file stream to upload from (use as input): */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(INFILE, OBJECTPOINT, 9),

				/* Buffer to receive error messages in, must be at least CURL_ERROR_SIZE
				* bytes big. If this is not used, error messages go to stderr instead: */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(ERRORBUFFER, OBJECTPOINT, 10),

				/* Function that will be called to store the output (instead of fwrite). The
				* parameters will use fwrite() syntax, make sure to follow them. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(WRITEFUNCTION, FUNCTIONPOINT, 11),

				/* Function that will be called to read the input (instead of fread). The
				* parameters will use fread() syntax, make sure to follow them. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(READFUNCTION, FUNCTIONPOINT, 12),

				/* Time-out the read operation after this amount of seconds */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TIMEOUT, LONG, 13),

				/* If the CURLOPT_INFILE is used, this can be used to inform libcurl about
				* how large the file being sent really is. That allows better error
				* checking and better verifies that the upload was successful. -1 means
				* unknown size.
				*
				* For large file support, there is also a _LARGE version of the key
				* which takes an OFF_T type, allowing platforms with larger OFF_T
				* sizes to handle larger files.  See below for INFILESIZE_LARGE.
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(INFILESIZE, LONG, 14),

				/* POST static input fields. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(POSTFIELDS, OBJECTPOINT, 15),

				/* Set the referrer page (needed by some CGIs) */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(REFERER, OBJECTPOINT, 16),

				/* Set the FTP PORT string (interface name, named or numerical IP address)
				Use i.e '-' to use default address. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTPPORT, OBJECTPOINT, 17),

				/* Set the User-Agent string (examined by some CGIs) */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(USERAGENT, OBJECTPOINT, 18),

				/* If the download receives less than "low speed limit" bytes/second
				* during "low speed time" seconds, the operations is aborted.
				* You could i.e if you have a pretty high speed connection, abort if
				* it is less than 2000 bytes/sec during 20 seconds.
				*/

				/* Set the "low speed limit" */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(LOW_SPEED_LIMIT, LONG, 19),

				/* Set the "low speed time" */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(LOW_SPEED_TIME, LONG, 20),

				/* Set the continuation offset.
				*
				* Note there is also a _LARGE version of this key which uses
				* OFF_T types, allowing for large file offsets on platforms which
				* use larger-than-32-bit OFF_T's.  Look below for RESUME_FROM_LARGE.
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RESUME_FROM, LONG, 21),

				/* Set cookie in request: */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(COOKIE, OBJECTPOINT, 22),

				/* This points to a linked list of headers, struct curl_slist kind */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HTTPHEADER, OBJECTPOINT, 23),

				/* This points to a linked list of post entries, struct curl_httppost */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HTTPPOST, OBJECTPOINT, 24),

				/* name of the file keeping your private SSL-certificate */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSLCERT, OBJECTPOINT, 25),

				/* password for the SSL or SSH private key */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(KEYPASSWD, OBJECTPOINT, 26),

				/* send TYPE parameter? */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CRLF, LONG, 27),

				/* send linked-list of QUOTE commands */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(QUOTE, OBJECTPOINT, 28),

				/* send FILE * or void * to store headers to, if you use a callback it
				is simply passed to the callback unmodified */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(WRITEHEADER, OBJECTPOINT, 29),

				/* point to a file to read the initial cookies from, also enables
				"cookie awareness" */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(COOKIEFILE, OBJECTPOINT, 31),

				/* What version to specifically try to use.
				See CURL_SSLVERSION defines below. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSLVERSION, LONG, 32),

				/* What kind of HTTP time condition to use, see defines */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TIMECONDITION, LONG, 33),

				/* Time to use with the above condition. Specified in number of seconds
				since 1 Jan 1970 */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TIMEVALUE, LONG, 34),

				/* 35 = OBSOLETE */

				/* Custom request, for customizing the get command like
				HTTP: DELETE, TRACE and others
				FTP: to use a different list command
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CUSTOMREQUEST, OBJECTPOINT, 36),

				/* HTTP request, for odd commands like DELETE, TRACE and others */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(STDERR, OBJECTPOINT, 37),

				/* 38 is not used */

				/* send linked-list of post-transfer QUOTE commands */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(POSTQUOTE, OBJECTPOINT, 39),

				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(WRITEINFO, OBJECTPOINT, 40), /* DEPRECATED, do not use! */

				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(VERBOSE, LONG, 41),      /* talk a lot */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HEADER, LONG, 42),       /* throw the header out too */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(NOPROGRESS, LONG, 43),   /* shut off the progress meter */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(NOBODY, LONG, 44),       /* use HEAD to get http document */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FAILONERROR, LONG, 45),  /* no output on http error codes >= 300 */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(UPLOAD, LONG, 46),       /* this is an upload */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(POST, LONG, 47),         /* HTTP POST method */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(DIRLISTONLY, LONG, 48),  /* bare names when listing directories */

				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(APPEND, LONG, 50),       /* Append instead of overwrite on upload! */

				/* Specify whether to read the user+password from the .netrc or the URL.
				* This must be one of the CURL_NETRC_* enums below. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(NETRC, LONG, 51),

				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FOLLOWLOCATION, LONG, 52),  /* use Location: Luke! */

				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TRANSFERTEXT, LONG, 53), /* transfer data in text/ASCII format */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PUT, LONG, 54),          /* HTTP PUT */

				/* 55 = OBSOLETE */

				/* DEPRECATED
				* Function that will be called instead of the internal progress display
				* function. This function should be defined as the curl_progress_callback
				* prototype defines. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROGRESSFUNCTION, FUNCTIONPOINT, 56),

				/* Data passed to the CURLOPT_PROGRESSFUNCTION and CURLOPT_XFERINFOFUNCTION
				callbacks */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROGRESSDATA, OBJECTPOINT, 57),
				CURLOPT_XFERINFODATA = CURLOPT_PROGRESSDATA,

				/* We want the referrer field set automatically when following locations */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(AUTOREFERER, LONG, 58),

				/* Port of the proxy, can be set in the proxy string as well with:
				"[host]:[port]" */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROXYPORT, LONG, 59),

				/* size of the POST input data, if strlen() is not good to use */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(POSTFIELDSIZE, LONG, 60),

				/* tunnel non-http operations through a HTTP proxy */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HTTPPROXYTUNNEL, LONG, 61),

				/* Set the interface string to use as outgoing network interface */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(INTERFACE, OBJECTPOINT, 62),

				/* Set the krb4/5 security level, this also enables krb4/5 awareness.  This
				* is a string, 'clear', 'safe', 'confidential' or 'private'.  If the string
				* is set but doesn't match one of these, 'private' will be used.  */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(KRBLEVEL, OBJECTPOINT, 63),

				/* Set if we should verify the peer in ssl handshake, set 1 to verify. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSL_VERIFYPEER, LONG, 64),

				/* The CApath or CAfile used to validate the peer certificate
				this option is used only if SSL_VERIFYPEER is true */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CAINFO, OBJECTPOINT, 65),

				/* 66 = OBSOLETE */
				/* 67 = OBSOLETE */

				/* Maximum number of http redirects to follow */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(MAXREDIRS, LONG, 68),

				/* Pass a LONG set to 1 to get the date of the requested document (if
				possible)! Pass a zero to shut it off. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FILETIME, LONG, 69),

				/* This points to a linked list of telnet options */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TELNETOPTIONS, OBJECTPOINT, 70),

				/* Max amount of cached alive connections */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(MAXCONNECTS, LONG, 71),

				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CLOSEPOLICY, LONG, 72), /* DEPRECATED, do not use! */

				/* 73 = OBSOLETE */

				/* Set to explicitly use a new connection for the upcoming transfer.
				Do not use this unless you're absolutely sure of this, as it makes the
				operation slower and is less friendly for the network. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FRESH_CONNECT, LONG, 74),

				/* Set to explicitly forbid the upcoming transfer's connection to be re-used
				when done. Do not use this unless you're absolutely sure of this, as it
				makes the operation slower and is less friendly for the network. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FORBID_REUSE, LONG, 75),

				/* Set to a file name that contains random data for libcurl to use to
				seed the random engine when doing SSL connects. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RANDOM_FILE, OBJECTPOINT, 76),

				/* Set to the Entropy Gathering Daemon socket pathname */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(EGDSOCKET, OBJECTPOINT, 77),

				/* Time-out connect operations after this amount of seconds, if connects are
				OK within this time, then fine... This only aborts the connect phase. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CONNECTTIMEOUT, LONG, 78),

				/* Function that will be called to store headers (instead of fwrite). The
				* parameters will use fwrite() syntax, make sure to follow them. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HEADERFUNCTION, FUNCTIONPOINT, 79),

				/* Set this to force the HTTP request to get back to GET. Only really usable
				if POST, PUT or a custom request have been used first.
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HTTPGET, LONG, 80),

				/* Set if we should verify the Common name from the peer certificate in ssl
				* handshake, set 1 to check existence, 2 to ensure that it matches the
				* provided hostname. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSL_VERIFYHOST, LONG, 81),

				/* Specify which file name to write all known cookies in after completed
				operation. Set file name to "-" (dash) to make it go to stdout. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(COOKIEJAR, OBJECTPOINT, 82),

				/* Specify which SSL ciphers to use */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSL_CIPHER_LIST, OBJECTPOINT, 83),

				/* Specify which HTTP version to use! This must be set to one of the
				CURL_HTTP_VERSION* enums set below. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HTTP_VERSION, LONG, 84),

				/* Specifically switch on or off the FTP engine's use of the EPSV command. By
				default, that one will always be attempted before the more traditional
				PASV command. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTP_USE_EPSV, LONG, 85),

				/* type of the file keeping your SSL-certificate ("DER", "PEM", "ENG") */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSLCERTTYPE, OBJECTPOINT, 86),

				/* name of the file keeping your private SSL-key */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSLKEY, OBJECTPOINT, 87),

				/* type of the file keeping your private SSL-key ("DER", "PEM", "ENG") */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSLKEYTYPE, OBJECTPOINT, 88),

				/* crypto engine for the SSL-sub system */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSLENGINE, OBJECTPOINT, 89),

				/* set the crypto engine for the SSL-sub system as default
				the param has no meaning...
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSLENGINE_DEFAULT, LONG, 90),

				/* Non-zero value means to use the global dns cache */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(DNS_USE_GLOBAL_CACHE, LONG, 91), /* DEPRECATED, do not use! */

				/* DNS cache timeout */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(DNS_CACHE_TIMEOUT, LONG, 92),

				/* send linked-list of pre-transfer QUOTE commands */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PREQUOTE, OBJECTPOINT, 93),

				/* set the debug function */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(DEBUGFUNCTION, FUNCTIONPOINT, 94),

				/* set the data for the debug function */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(DEBUGDATA, OBJECTPOINT, 95),

				/* mark this as start of a cookie session */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(COOKIESESSION, LONG, 96),

				/* The CApath directory used to validate the peer certificate
				this option is used only if SSL_VERIFYPEER is true */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CAPATH, OBJECTPOINT, 97),

				/* Instruct libcurl to use a smaller receive buffer */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(BUFFERSIZE, LONG, 98),

				/* Instruct libcurl to not use any signal/alarm handlers, even when using
				timeouts. This option is useful for multi-threaded applications.
				See libcurl-the-guide for more background information. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(NOSIGNAL, LONG, 99),

				/* Provide a CURLShare for mutexing non-ts data */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SHARE, OBJECTPOINT, 100),

				/* indicates type of proxy. accepted values are CURLPROXY_HTTP (default),
				CURLPROXY_SOCKS4, CURLPROXY_SOCKS4A and CURLPROXY_SOCKS5. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROXYTYPE, LONG, 101),

				/* Set the Accept-Encoding string. Use this to tell a server you would like
				the response to be compressed. Before 7.21.6, this was known as
				CURLOPT_ENCODING */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(ACCEPT_ENCODING, OBJECTPOINT, 102),

				/* Set pointer to private data */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PRIVATE, OBJECTPOINT, 103),

				/* Set aliases for HTTP 200 in the HTTP Response header */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HTTP200ALIASES, OBJECTPOINT, 104),

				/* Continue to send authentication (user+password) when following locations,
				even when hostname changed. This can potentially send off the name
				and password to whatever host the server decides. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(UNRESTRICTED_AUTH, LONG, 105),

				/* Specifically switch on or off the FTP engine's use of the EPRT command (
				it also disables the LPRT attempt). By default, those ones will always be
				attempted before the good old traditional PORT command. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTP_USE_EPRT, LONG, 106),

				/* Set this to a bitmask value to enable the particular authentications
				methods you like. Use this in combination with CURLOPT_USERPWD.
				Note that setting multiple bits may cause extra network round-trips. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HTTPAUTH, LONG, 107),

				/* Set the ssl context callback function, currently only for OpenSSL ssl_ctx
				in second argument. The function must be matching the
				curl_ssl_ctx_callback proto. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSL_CTX_FUNCTION, FUNCTIONPOINT, 108),

				/* Set the userdata for the ssl context callback function's third
				argument */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSL_CTX_DATA, OBJECTPOINT, 109),

				/* FTP Option that causes missing dirs to be created on the remote server.
				In 7.19.4 we introduced the convenience enums for this option using the
				CURLFTP_CREATE_DIR prefix.
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTP_CREATE_MISSING_DIRS, LONG, 110),

				/* Set this to a bitmask value to enable the particular authentications
				methods you like. Use this in combination with CURLOPT_PROXYUSERPWD.
				Note that setting multiple bits may cause extra network round-trips. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROXYAUTH, LONG, 111),

				/* FTP option that changes the timeout, in seconds, associated with
				getting a response.  This is different from transfer timeout time and
				essentially places a demand on the FTP server to acknowledge commands
				in a timely manner. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTP_RESPONSE_TIMEOUT, LONG, 112),
				CURLOPT_SERVER_RESPONSE_TIMEOUT =  CURLOPT_FTP_RESPONSE_TIMEOUT,

				/* Set this option to one of the CURL_IPRESOLVE_* defines (see below) to
				tell libcurl to resolve names to those IP versions only. This only has
				affect on systems with support for more than one, i.e IPv4 _and_ IPv6. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(IPRESOLVE, LONG, 113),

				/* Set this option to limit the size of a file that will be downloaded from
				an HTTP or FTP server.

				Note there is also _LARGE version which adds large file support for
				platforms which have larger OFF_T sizes.  See MAXFILESIZE_LARGE below. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(MAXFILESIZE, LONG, 114),

				/* See the comment for INFILESIZE above, but in short, specifies
				* the size of the file being uploaded.  -1 means unknown.
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(INFILESIZE_LARGE, OFF_T, 115),

				/* Sets the continuation offset.  There is also a LONG version of this;
				* look above for RESUME_FROM.
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RESUME_FROM_LARGE, OFF_T, 116),

				/* Sets the maximum size of data that will be downloaded from
				* an HTTP or FTP server.  See MAXFILESIZE above for the LONG version.
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(MAXFILESIZE_LARGE, OFF_T, 117),

				/* Set this option to the file name of your .netrc file you want libcurl
				to parse (using the CURLOPT_NETRC option). If not set, libcurl will do
				a poor attempt to find the user's home directory and check for a .netrc
				file in there. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(NETRC_FILE, OBJECTPOINT, 118),

				/* Enable SSL/TLS for FTP, pick one of:
				CURLUSESSL_TRY     - try using SSL, proceed anyway otherwise
				CURLUSESSL_CONTROL - SSL for the control connection or fail
				CURLUSESSL_ALL     - SSL for all communication or fail
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(USE_SSL, LONG, 119),

				/* The _LARGE version of the standard POSTFIELDSIZE option */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(POSTFIELDSIZE_LARGE, OFF_T, 120),

				/* Enable/disable the TCP Nagle algorithm */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TCP_NODELAY, LONG, 121),

				/* 122 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
				/* 123 OBSOLETE. Gone in 7.16.0 */
				/* 124 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
				/* 125 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
				/* 126 OBSOLETE, used in 7.12.3. Gone in 7.13.0 */
				/* 127 OBSOLETE. Gone in 7.16.0 */
				/* 128 OBSOLETE. Gone in 7.16.0 */

				/* When FTP over SSL/TLS is selected (with CURLOPT_USE_SSL), this option
				can be used to change libcurl's default action which is to first try
				"AUTH SSL" and then "AUTH TLS" in this order, and proceed when a OK
				response has been received.

				Available parameters are:
				CURLFTPAUTH_DEFAULT - let libcurl decide
				CURLFTPAUTH_SSL     - try "AUTH SSL" first, then TLS
				CURLFTPAUTH_TLS     - try "AUTH TLS" first, then SSL
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTPSSLAUTH, LONG, 129),

				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(IOCTLFUNCTION, FUNCTIONPOINT, 130),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(IOCTLDATA, OBJECTPOINT, 131),

				/* 132 OBSOLETE. Gone in 7.16.0 */
				/* 133 OBSOLETE. Gone in 7.16.0 */

				/* zero terminated string for pass on to the FTP server when asked for
				"account" info */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTP_ACCOUNT, OBJECTPOINT, 134),

				/* feed cookies into cookie engine */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(COOKIELIST, OBJECTPOINT, 135),

				/* ignore Content-Length */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(IGNORE_CONTENT_LENGTH, LONG, 136),

				/* Set to non-zero to skip the IP address received in a 227 PASV FTP server
				response. Typically used for FTP-SSL purposes but is not restricted to
				that. libcurl will then instead use the same IP address it used for the
				control connection. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTP_SKIP_PASV_IP, LONG, 137),

				/* Select "file method" to use when doing FTP, see the curl_ftpmethod
				above. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTP_FILEMETHOD, LONG, 138),

				/* Local port number to bind the socket to */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(LOCALPORT, LONG, 139),

				/* Number of ports to try, including the first one set with LOCALPORT.
				Thus, setting it to 1 will make no additional attempts but the first.
				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(LOCALPORTRANGE, LONG, 140),

				/* no transfer, set up connection and let application use the socket by
				extracting it with CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LASTSOCKET */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CONNECT_ONLY, LONG, 141),

				/* Function that will be called to convert from the
				network encoding (instead of using the iconv calls in libcurl) */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CONV_FROM_NETWORK_FUNCTION, FUNCTIONPOINT, 142),

				/* Function that will be called to convert to the
				network encoding (instead of using the iconv calls in libcurl) */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CONV_TO_NETWORK_FUNCTION, FUNCTIONPOINT, 143),

				/* Function that will be called to convert from UTF8
				(instead of using the iconv calls in libcurl)
				Note that this is used only for SSL certificate processing */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CONV_FROM_UTF8_FUNCTION, FUNCTIONPOINT, 144),

				/* if the connection proceeds too quickly then need to slow it down */
				/* limit-rate: maximum number of bytes per second to send or receive */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(MAX_SEND_SPEED_LARGE, OFF_T, 145),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(MAX_RECV_SPEED_LARGE, OFF_T, 146),

				/* Pointer to command string to send if USER/PASS fails. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTP_ALTERNATIVE_TO_USER, OBJECTPOINT, 147),

				/* callback function for setting socket options */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SOCKOPTFUNCTION, FUNCTIONPOINT, 148),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SOCKOPTDATA, OBJECTPOINT, 149),

				/* set to 0 to disable session ID re-use for this transfer, default is
				enabled (== 1) */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSL_SESSIONID_CACHE, LONG, 150),

				/* allowed SSH authentication methods */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSH_AUTH_TYPES, LONG, 151),

				/* Used by scp/sftp to do public/private key authentication */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSH_PUBLIC_KEYFILE, OBJECTPOINT, 152),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSH_PRIVATE_KEYFILE, OBJECTPOINT, 153),

				/* Send CCC (Clear Command Channel) after authentication */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTP_SSL_CCC, LONG, 154),

				/* Same as TIMEOUT and CONNECTTIMEOUT, but with ms resolution */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TIMEOUT_MS, LONG, 155),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CONNECTTIMEOUT_MS, LONG, 156),

				/* set to zero to disable the libcurl's decoding and thus pass the raw body
				data to the application even when it is encoded/compressed */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HTTP_TRANSFER_DECODING, LONG, 157),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(HTTP_CONTENT_DECODING, LONG, 158),

				/* Permission used when creating new files and directories on the remote
				server for protocols that support it, SFTP/SCP/FILE */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(NEW_FILE_PERMS, LONG, 159),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(NEW_DIRECTORY_PERMS, LONG, 160),

				/* Set the behaviour of POST when redirecting. Values must be set to one
				of CURL_REDIR* defines below. This used to be called CURLOPT_POST301 */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(POSTREDIR, LONG, 161),

				/* used by scp/sftp to verify the host's public key */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSH_HOST_PUBLIC_KEY_MD5, OBJECTPOINT, 162),

				/* Callback function for opening socket (instead of socket(2)). Optionally,
				callback is able change the address or refuse to connect returning
				CURL_SOCKET_BAD.  The callback should have type
				curl_opensocket_callback */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(OPENSOCKETFUNCTION, FUNCTIONPOINT, 163),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(OPENSOCKETDATA, OBJECTPOINT, 164),

				/* POST volatile input fields. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(COPYPOSTFIELDS, OBJECTPOINT, 165),

				/* set transfer mode (;type=<a|i>) when doing FTP via an HTTP proxy */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROXY_TRANSFER_MODE, LONG, 166),

				/* Callback function for seeking in the input stream */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SEEKFUNCTION, FUNCTIONPOINT, 167),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SEEKDATA, OBJECTPOINT, 168),

				/* CRL file */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CRLFILE, OBJECTPOINT, 169),

				/* Issuer certificate */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(ISSUERCERT, OBJECTPOINT, 170),

				/* (IPv6) Address scope */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(ADDRESS_SCOPE, LONG, 171),

				/* Collect certificate chain info and allow it to get retrievable with
				CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_CERTINFO after the transfer is complete. (Unfortunately) only
				working with OpenSSL-powered builds. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CERTINFO, LONG, 172),

				/* "name" and "pwd" to use when fetching. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(USERNAME, OBJECTPOINT, 173),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PASSWORD, OBJECTPOINT, 174),

				/* "name" and "pwd" to use with Proxy when fetching. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROXYUSERNAME, OBJECTPOINT, 175),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROXYPASSWORD, OBJECTPOINT, 176),

				/* Comma separated list of hostnames defining no-proxy zones. These should
				match both hostnames directly, and hostnames within a domain. For
				example, local.com will match local.com and www.local.com, but NOT
				notlocal.com or www.notlocal.com. For compatibility with other
				implementations of this, .local.com will be considered to be the same as
				local.com. A single * is the only valid wildcard, and effectively
				disables the use of proxy. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(NOPROXY, OBJECTPOINT, 177),

				/* block size for TFTP transfers */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TFTP_BLKSIZE, LONG, 178),

				/* Socks Service */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SOCKS5_GSSAPI_SERVICE, OBJECTPOINT, 179),

				/* Socks Service */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SOCKS5_GSSAPI_NEC, LONG, 180),

				/* set the bitmask for the protocols that are allowed to be used for the
				transfer, which thus helps the app which takes URLs from users or other
				external inputs and want to restrict what protocol(s) to deal
				with. Defaults to CURLPROTO_ALL. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(PROTOCOLS, LONG, 181),

				/* set the bitmask for the protocols that libcurl is allowed to follow to,
				as a subset of the CURLOPT_PROTOCOLS ones. That means the protocol needs
				to be set in both bitmasks to be allowed to get redirected to. Defaults
				to all protocols except FILE and SCP. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(REDIR_PROTOCOLS, LONG, 182),

				/* set the SSH knownhost file name to use */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSH_KNOWNHOSTS, OBJECTPOINT, 183),

				/* set the SSH host key callback, must point to a curl_sshkeycallback
				function */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSH_KEYFUNCTION, FUNCTIONPOINT, 184),

				/* set the SSH host key callback custom pointer */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSH_KEYDATA, OBJECTPOINT, 185),

				/* set the SMTP mail originator */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(MAIL_FROM, OBJECTPOINT, 186),

				/* set the SMTP mail receiver(s) */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(MAIL_RCPT, OBJECTPOINT, 187),

				/* FTP: send PRET before PASV */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FTP_USE_PRET, LONG, 188),

				/* RTSP request method (OPTIONS, SETUP, PLAY, etc...) */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RTSP_REQUEST, LONG, 189),

				/* The RTSP session identifier */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RTSP_SESSION_ID, OBJECTPOINT, 190),

				/* The RTSP stream URI */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RTSP_STREAM_URI, OBJECTPOINT, 191),

				/* The Transport: header to use in RTSP requests */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RTSP_TRANSPORT, OBJECTPOINT, 192),

				/* Manually initialize the client RTSP CSeq for this handle */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RTSP_CLIENT_CSEQ, LONG, 193),

				/* Manually initialize the server RTSP CSeq for this handle */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RTSP_SERVER_CSEQ, LONG, 194),

				/* The stream to pass to INTERLEAVEFUNCTION. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(INTERLEAVEDATA, OBJECTPOINT, 195),

				/* Let the application define a custom write method for RTP data */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(INTERLEAVEFUNCTION, FUNCTIONPOINT, 196),

				/* Turn on wildcard matching */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(WILDCARDMATCH, LONG, 197),

				/* Directory matching callback called before downloading of an
				individual file (chunk) started */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CHUNK_BGN_FUNCTION, FUNCTIONPOINT, 198),

				/* Directory matching callback called after the file (chunk)
				was downloaded, or skipped */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CHUNK_END_FUNCTION, FUNCTIONPOINT, 199),

				/* Change match (fnmatch-like) callback for wildcard matching */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FNMATCH_FUNCTION, FUNCTIONPOINT, 200),

				/* Let the application define custom chunk data pointer */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CHUNK_DATA, OBJECTPOINT, 201),

				/* FNMATCH_FUNCTION user pointer */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(FNMATCH_DATA, OBJECTPOINT, 202),

				/* send linked-list of name:port:address sets */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(RESOLVE, OBJECTPOINT, 203),

				/* Set a username for authenticated TLS */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TLSAUTH_USERNAME, OBJECTPOINT, 204),

				/* Set a password for authenticated TLS */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TLSAUTH_PASSWORD, OBJECTPOINT, 205),

				/* Set authentication type for authenticated TLS */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TLSAUTH_TYPE, OBJECTPOINT, 206),

				/* Set to 1 to enable the "TE:" header in HTTP requests to ask for
				compressed transfer-encoded responses. Set to 0 to disable the use of TE:
				in outgoing requests. The current default is 0, but it might change in a
				future libcurl release.

				libcurl will ask for the compressed methods it knows of, and if that
				isn't any, it will not ask for transfer-encoding at all even if this
				option is set to 1.

				*/
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TRANSFER_ENCODING, LONG, 207),

				/* Callback function for closing socket (instead of close(2)). The callback
				should have type curl_closesocket_callback */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CLOSESOCKETFUNCTION, FUNCTIONPOINT, 208),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(CLOSESOCKETDATA, OBJECTPOINT, 209),

				/* allow GSSAPI credential delegation */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(GSSAPI_DELEGATION, LONG, 210),

				/* Set the name servers to use for DNS resolution */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(DNS_SERVERS, OBJECTPOINT, 211),

				/* Time-out accept operations (currently for FTP only) after this amount
				of miliseconds. */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(ACCEPTTIMEOUT_MS, LONG, 212),

				/* Set TCP keepalive */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TCP_KEEPALIVE, LONG, 213),

				/* non-universal keepalive knobs (Linux, AIX, HP-UX, more) */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TCP_KEEPIDLE, LONG, 214),
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(TCP_KEEPINTVL, LONG, 215),

				/* Enable/disable specific SSL features with a bitmask, see CURLSSLOPT_* */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SSL_OPTIONS, LONG, 216),

				/* Set the SMTP auth originator */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(MAIL_AUTH, OBJECTPOINT, 217),

				/* Enable/disable SASL initial response */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(SASL_IR, LONG, 218),

				/* Function that will be called instead of the internal progress display
				* function. This function should be defined as the curl_xferinfo_callback
				* prototype defines. (Deprecates CURLOPT_PROGRESSFUNCTION) */
				CPPCOMPONENTS_LIBCURL_LIBUV_CINIT(XFERINFOFUNCTION, FUNCTIONPOINT, 219),

				CURLOPT_LASTENTRY /* the last unused */
			};
		}

		namespace Info{
#define CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_STRING   0x100000
#define CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG     0x200000
#define CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE   0x300000
#define CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_SLIST    0x400000
#define CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_MASK     0x0fffff
#define CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_TYPEMASK 0xf00000

			 enum {
				CURLINFO_NONE, /* first, never use this */
				CURLINFO_EFFECTIVE_URL = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_STRING + 1,
				CURLINFO_RESPONSE_CODE = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 2,
				CURLINFO_TOTAL_TIME = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 3,
				CURLINFO_NAMELOOKUP_TIME = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 4,
				CURLINFO_CONNECT_TIME = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 5,
				CURLINFO_PRETRANSFER_TIME = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 6,
				CURLINFO_SIZE_UPLOAD = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 7,
				CURLINFO_SIZE_DOWNLOAD = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 8,
				CURLINFO_SPEED_DOWNLOAD = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 9,
				CURLINFO_SPEED_UPLOAD = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 10,
				CURLINFO_HEADER_SIZE = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 11,
				CURLINFO_REQUEST_SIZE = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 12,
				CURLINFO_SSL_VERIFYRESULT = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 13,
				CURLINFO_FILETIME = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 14,
				CURLINFO_CONTENT_LENGTH_DOWNLOAD = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 15,
				CURLINFO_CONTENT_LENGTH_UPLOAD = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 16,
				CURLINFO_STARTTRANSFER_TIME = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 17,
				CURLINFO_CONTENT_TYPE = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_STRING + 18,
				CURLINFO_REDIRECT_TIME = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 19,
				CURLINFO_REDIRECT_COUNT = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 20,
				CURLINFO_PRIVATE = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_STRING + 21,
				CURLINFO_HTTP_CONNECTCODE = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 22,
				CURLINFO_HTTPAUTH_AVAIL = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 23,
				CURLINFO_PROXYAUTH_AVAIL = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 24,
				CURLINFO_OS_ERRNO = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 25,
				CURLINFO_NUM_CONNECTS = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 26,
				CURLINFO_SSL_ENGINES = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_SLIST + 27,
				CURLINFO_COOKIELIST = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_SLIST + 28,
				CURLINFO_LASTSOCKET = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 29,
				CURLINFO_FTP_ENTRY_PATH = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_STRING + 30,
				CURLINFO_REDIRECT_URL = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_STRING + 31,
				CURLINFO_PRIMARY_IP = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_STRING + 32,
				CURLINFO_APPCONNECT_TIME = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE + 33,
				CURLINFO_CERTINFO = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_SLIST + 34,
				CURLINFO_CONDITION_UNMET = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 35,
				CURLINFO_RTSP_SESSION_ID = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_STRING + 36,
				CURLINFO_RTSP_CLIENT_CSEQ = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 37,
				CURLINFO_RTSP_SERVER_CSEQ = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 38,
				CURLINFO_RTSP_CSEQ_RECV = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 39,
				CURLINFO_PRIMARY_PORT = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 40,
				CURLINFO_LOCAL_IP = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_STRING + 41,
				CURLINFO_LOCAL_PORT = CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG + 42,
				/* Fill in new entries below here! */

				CURLINFO_LASTONE = 42
			} ;

		}
		/*
		* Bitmasks for CURLOPT_HTTPAUTH and CURLOPT_PROXYAUTH options:
		*
		* CURLAUTH_NONE         - No HTTP authentication
		* CURLAUTH_BASIC        - HTTP Basic authentication (default)
		* CURLAUTH_DIGEST       - HTTP Digest authentication
		* CURLAUTH_GSSNEGOTIATE - HTTP GSS-Negotiate authentication
		* CURLAUTH_NTLM         - HTTP NTLM authentication
		* CURLAUTH_DIGEST_IE    - HTTP Digest authentication with IE flavour
		* CURLAUTH_NTLM_WB      - HTTP NTLM authentication delegated to winbind helper
		* CURLAUTH_ONLY         - Use together with a single other type to force no
		*                         authentication or just that single type
		* CURLAUTH_ANY          - All fine types set
		* CURLAUTH_ANYSAFE      - All fine types except Basic
		*/

		namespace Auth{
			enum{
				CURLAUTH_NONE = ((unsigned long)0),
				CURLAUTH_BASIC = (((unsigned long)1) << 0),
				CURLAUTH_DIGEST = (((unsigned long)1) << 1),
				CURLAUTH_GSSNEGOTIATE = (((unsigned long)1) << 2),
				CURLAUTH_NTLM = (((unsigned long)1) << 3),
				CURLAUTH_DIGEST_IE = (((unsigned long)1) << 4),
				CURLAUTH_NTLM_WB = (((unsigned long)1) << 5),
				CURLAUTH_ONLY = (((unsigned long)1) << 31),
				CURLAUTH_ANY = (~CURLAUTH_DIGEST_IE),
				CURLAUTH_ANYSAFE = (~(CURLAUTH_BASIC | CURLAUTH_DIGEST_IE)),

				CURLSSH_AUTH_ANY = ~0,   /* all types supported by the server */
				CURLSSH_AUTH_NONE = 0,   /* none allowed, silly but complete */
				CURLSSH_AUTH_PUBLICKEY = (1 << 0),/* public/private key files */
				CURLSSH_AUTH_PASSWORD = (1 << 1), /* password */
				CURLSSH_AUTH_HOST = (1 << 2), /* host key files */
				CURLSSH_AUTH_KEYBOARD = (1 << 3), /* keyboard interactive */
				CURLSSH_AUTH_AGENT = (1 << 4),/* agent (ssh-agent, pageant...) */
				CURLSSH_AUTH_DEFAULT = CURLSSH_AUTH_ANY,

				CURLGSSAPI_DELEGATION_NONE = 0,      /* no delegation (default) */
				CURLGSSAPI_DELEGATION_POLICY_FLAG = (1 << 0), /* if permitted by policy */
				CURLGSSAPI_DELEGATION_FLAG = (1 << 1), /* delegate always */
			};
		}

	}
}


#undef CPPCOMPONENTS_LIBCURL_LIBUV_CURLOPTTYPE_LONG          
#undef CPPCOMPONENTS_LIBCURL_LIBUV_CURLOPTTYPE_OBJECTPOINT   
#undef CPPCOMPONENTS_LIBCURL_LIBUV_CURLOPTTYPE_FUNCTIONPOINT 
#undef CPPCOMPONENTS_LIBCURL_LIBUV_CURLOPTTYPE_OFF_T         

#undef CPPCOMPONENTS_LIBCURL_LIBUV_CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_STRING   
#undef CPPCOMPONENTS_LIBCURL_LIBUV_CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_LONG    
#undef CPPCOMPONENTS_LIBCURL_LIBUV_CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_DOUBLE 
#undef CPPCOMPONENTS_LIBCURL_LIBUV_CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_SLIST 
#undef CPPCOMPONENTS_LIBCURL_LIBUV_CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_MASK 
#undef CPPCOMPONENTS_LIBCURL_LIBUV_CPPCOMPONENTS_LIBCURL_LIBUV_CURLINFO_TYPEMASK


#undef CPPCOMPONENTS_LIBCURL_LIBUV_CINIT