#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path)
#else
#define MKDIR(path) mkdir(path, 0755)
#endif

static int ensure_uploads_directory(const char *dir_path) {
    if (MKDIR(dir_path) == 0) {
        return 0;
    }

    if (errno == EEXIST) {
        return 0;
    }

    perror("Failed to create uploads directory");
    return -1;
}

int main(int argc, char *argv[]) {
    const char *uploads_dir = "uploads";
    const char *target_name = "sample_upload.bin";
    const char *mode = "wb";
    const unsigned char sample_bytes[] = { 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x55, 0x70, 0x6C, 0x6F, 0x61, 0x64, 0x21, 0x0A };

    if (argc > 1) {
        target_name = argv[1];
    }
    if (argc > 2) {
        mode = argv[2];
    }

    if (strcmp(mode, "wb") != 0 && strcmp(mode, "w") != 0) {
        fprintf(stderr, "Invalid mode '%s'. Use 'wb' (binary) or 'w' (text).\n", mode);
        return 1;
    }

    if (ensure_uploads_directory(uploads_dir) != 0) {
        return 1;
    }

    char output_path[512];
    int path_len = snprintf(output_path, sizeof(output_path), "%s/%s", uploads_dir, target_name);
    if (path_len < 0 || (size_t)path_len >= sizeof(output_path)) {
        fprintf(stderr, "Output path is too long.\n");
        return 1;
    }

    FILE *file = fopen(output_path, mode);
    if (file == NULL) {
        perror("Failed to open output file");
        return 1;
    }

    size_t bytes_written = fwrite(sample_bytes, sizeof(unsigned char), sizeof(sample_bytes), file);
    if (bytes_written != sizeof(sample_bytes)) {
        perror("Failed to write all bytes");
        fclose(file);
        return 1;
    }

    if (fclose(file) != 0) {
        perror("Failed to close output file");
        return 1;
    }

    printf("Wrote %zu bytes to %s using mode '%s'.\n", bytes_written, output_path, mode);
    return 0;
}
