/**
 * Created March 15, 2021
 * 
 * This work is a part of ESP-Line-Notify library
 * Copyright (c) 2021, K. Suwatchai (Mobizt)
 * 
 * The MIT License (MIT)
 * Copyright (c) 2021, K. Suwatchai (Mobizt)
 * 
 * 
 * Permission is hereby granted, free of charge, to any person returning a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef LINENOTIFY_HTTP_CODE_H_
#define LINENOTIFY_HTTP_CODE_H_

#define LINENOTIFY_DEFAULT_TCP_TIMEOUT 10000 //10 seconds

/// HTTP client errors
#define LINENOTIFY_ERROR_HTTPC_ERROR_CONNECTION_REFUSED (-1)
#define LINENOTIFY_ERROR_HTTPC_ERROR_SEND_HEADER_FAILED (-2)
#define LINENOTIFY_ERROR_HTTPC_ERROR_SEND_PAYLOAD_FAILED (-3)
#define LINENOTIFY_ERROR_HTTPC_ERROR_NOT_CONNECTED (-4)
#define LINENOTIFY_ERROR_HTTPC_ERROR_CONNECTION_LOST (-5)
#define LINENOTIFY_ERROR_HTTPC_ERROR_NO_STREAM (-6)
#define LINENOTIFY_ERROR_HTTPC_ERROR_NO_HTTP_SERVER (-7)
#define LINENOTIFY_ERROR_HTTPC_ERROR_TOO_LESS_RAM (-8)
#define LINENOTIFY_ERROR_HTTPC_ERROR_ENCODING (-9)
#define LINENOTIFY_ERROR_HTTPC_ERROR_STREAM_WRITE (-10)
#define LINENOTIFY_ERROR_HTTPC_ERROR_READ_TIMEOUT (-11)
#define LINENOTIFY_ERROR_BUFFER_OVERFLOW (-12)
#define LINENOTIFY_ERROR_FILE_IO_ERROR -13
#define LINENOTIFY_ERROR_FILE_NOT_FOUND -14

/// HTTP codes see RFC7231

#define LINENOTIFY_ERROR_HTTP_CODE_OK 200
#define LINENOTIFY_ERROR_HTTP_CODE_NON_AUTHORITATIVE_INFORMATION 203
#define LINENOTIFY_ERROR_HTTP_CODE_NO_CONTENT 204
#define LINENOTIFY_ERROR_HTTP_CODE_MOVED_PERMANENTLY 301
#define LINENOTIFY_ERROR_HTTP_CODE_FOUND 302
#define LINENOTIFY_ERROR_HTTP_CODE_USE_PROXY 305
#define LINENOTIFY_ERROR_HTTP_CODE_TEMPORARY_REDIRECT 307
#define LINENOTIFY_ERROR_HTTP_CODE_PERMANENT_REDIRECT 308
#define LINENOTIFY_ERROR_HTTP_CODE_BAD_REQUEST 400
#define LINENOTIFY_ERROR_HTTP_CODE_UNAUTHORIZED 401
#define LINENOTIFY_ERROR_HTTP_CODE_FORBIDDEN 403
#define LINENOTIFY_ERROR_HTTP_CODE_NOT_FOUND 404
#define LINENOTIFY_ERROR_HTTP_CODE_METHOD_NOT_ALLOWED 405
#define LINENOTIFY_ERROR_HTTP_CODE_NOT_ACCEPTABLE 406
#define LINENOTIFY_ERROR_HTTP_CODE_PROXY_AUTHENTICATION_REQUIRED 407
#define LINENOTIFY_ERROR_HTTP_CODE_REQUEST_TIMEOUT 408
#define LINENOTIFY_ERROR_HTTP_CODE_LENGTH_REQUIRED 411
#define LINENOTIFY_ERROR_HTTP_CODE_PRECONDITION_FAILED 412
#define LINENOTIFY_ERROR_HTTP_CODE_PAYLOAD_TOO_LARGE 413
#define LINENOTIFY_ERROR_HTTP_CODE_URI_TOO_LONG 414
#define LINENOTIFY_ERROR_HTTP_CODE_MISDIRECTED_REQUEST 421
#define LINENOTIFY_ERROR_HTTP_CODE_UNPROCESSABLE_ENTITY 422
#define LINENOTIFY_ERROR_HTTP_CODE_TOO_MANY_REQUESTS 429
#define LINENOTIFY_ERROR_HTTP_CODE_REQUEST_HEADER_FIELDS_TOO_LARGE 431
#define LINENOTIFY_ERROR_HTTP_CODE_INTERNAL_SERVER_ERROR 500
#define LINENOTIFY_ERROR_HTTP_CODE_NOT_IMPLEMENTED 501
#define LINENOTIFY_ERROR_HTTP_CODE_BAD_GATEWAY 502
#define LINENOTIFY_ERROR_HTTP_CODE_SERVICE_UNAVAILABLE 503
#define LINENOTIFY_ERROR_HTTP_CODE_GATEWAY_TIMEOUT 504
#define LINENOTIFY_ERROR_HTTP_CODE_HTTP_VERSION_NOT_SUPPORTED 505
#define LINENOTIFY_ERROR_HTTP_CODE_LOOP_DETECTED 508
#define LINENOTIFY_ERROR_HTTP_CODE_NETWORK_AUTHENTICATION_REQUIRED 511

#endif