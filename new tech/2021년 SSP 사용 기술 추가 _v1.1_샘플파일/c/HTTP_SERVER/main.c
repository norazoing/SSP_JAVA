#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>

#include <glib.h>
#include <microhttpd.h>
#include <json-c/json.h>
#include <curl/curl.h>

#define PORT 8080

/*
 * constructor 함수 : main 이전에 실행됨, GCC only
 *
 * eclipse에서 cygwin gdb 디버깅할 경우
 * gdb를 통한 프로그램의 콘솔 출력 버퍼가 정상동작 하지 않고
 * 실행 종료 후 한꺼번에 출력되는 경우가 있음.
 * 이를 피하기 위해 stdout, stderr의 buffering을 끄는 함수.
 * 만일 buffer가 꼭 필요하다면 아래 함수를 주석처리 할 것.
 */
void __attribute__((constructor)) console_setting_for_eclipse_debugging( void ){
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}

struct connection_info {
    char *buffer;
    size_t buffer_size;
};

size_t buffer_write(char *upload_data, size_t upload_data_size, struct connection_info *conn_info) {
    char *ptr = realloc(conn_info->buffer, conn_info->buffer_size + upload_data_size + 1);
    if (ptr == NULL)
        return 0; /* out of memory! */

    conn_info->buffer = ptr;
    memcpy(&(conn_info->buffer[conn_info->buffer_size]), upload_data, upload_data_size);
    conn_info->buffer_size += upload_data_size;
    conn_info->buffer[conn_info->buffer_size] = 0;

    return upload_data_size;
}

/**
 * 200(OK)로 응답 수행
 */
static enum MHD_Result response_result(struct MHD_Connection *connection,
        const char *page) {
    enum MHD_Result ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void*) page,
            MHD_RESPMEM_MUST_COPY);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

/**
 * 입력된 Status Code로 응답 수행
 */
static enum MHD_Result response_error(struct MHD_Connection *connection,
        int status_code) {
    enum MHD_Result ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_MUST_COPY);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);

    return ret;
}

/**
 * 접속이 완료되는 경우 호출되는 callback
 */
static void request_completed_callback(void *cls,
        struct MHD_Connection *connection,
        void **con_cls,
        enum MHD_RequestTerminationCode toe) {

    struct connection_info *con_info = *con_cls;
    if (con_info) {
        if (con_info->buffer) {
            free(con_info->buffer);
        }
        free(con_info);
    }
    *con_cls = NULL;
}

/**
 * 접속을 처리하는 callback
 */
static enum MHD_Result access_handler_callback(void *cls,
        struct MHD_Connection *connection,
        const char *url,
        const char *method,
        const char *version,
        const char *upload_data,
        size_t *upload_data_size,
        void **con_cls) {

    printf("[start line] Method: %s\n", method);
    printf("[start line] Request URI: %s\n", url);

    const char *host = MHD_lookup_connection_value(connection, MHD_HEADER_KIND, "Host");
    printf("[header] Host: %s\n", host);

    // POST 방식 처리 로직
    if (strcmp(method, "POST") == 0) {
        struct connection_info *con_info = (struct connection_info *)*con_cls;
        // 최초 접속의 경우
        if (con_info == NULL) {
            con_info = calloc(1, sizeof(struct connection_info));
            if (con_info == NULL) {
                return MHD_NO;
            }
            *con_cls = con_info;
            return MHD_YES;
        }

        if (*upload_data_size != 0) {
            buffer_write((char *)upload_data, *upload_data_size, con_info);
            *upload_data_size = 0;
            return MHD_YES;
        } else {
            // POST 방식 body에 대한 처리 수행
            printf("[body] %s\n", con_info->buffer);
        }
    }
    // GET 방식 처리 로직
    if (strcmp(method, "GET") == 0) {
        printf("[body] 없음\n");
    }
    printf("\n");

    return response_result(connection, "Hello World!");
}

int main(int argc, char *argv[]) {

    // HTTP 데몬을 시작한다
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
        PORT,
        NULL,
        NULL,
        &access_handler_callback,
        NULL,
        MHD_OPTION_NOTIFY_COMPLETED,
        request_completed_callback,
        NULL,
        MHD_OPTION_END);
    if (daemon == NULL) {
        fprintf(stderr, "MHD_start_daemon() error\n");
        return EXIT_FAILURE;
    }

    while (true) {
        getc(stdin);
    }

    // HTTP 데몬을 종료한다
    MHD_stop_daemon(daemon);

    return EXIT_SUCCESS;
}
