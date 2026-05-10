# 📂 File Upload API (C Language)

## Overview
A simple HTTP-like server written in C that allows clients to upload files using sockets.

## Tech Stack
- C (GCC)
- POSIX sockets
- Basic file I/O

## Features
- Accept client connections
- Receive file metadata and content
- Store files in a local `uploads/` folder
- Return upload status

## Basic Flow
1. Server listens on a port.
2. Client connects and sends file with headers.
3. Server reads bytes and writes to disk.
4. Response is sent confirming upload success.

## Example Client Request (pseudo)
- POST /upload HTTP/1.1
- Filename: test.txt
- Content-Length: 512

- <file bytes> ```

## 🛠️ Suggested Learning Path
- Brush up on C fundamentals (if needed)
- Master file I/O: reading/writing files, handling errors
- Learn POSIX sockets: start with TCP client-server examples
- Get comfortable with GCC and Makefiles
- Practice debugging with gdb






# 🛠️ What You Can Build NOW (C Fundamentals Only)

## 1. File Writer Utility

**What it is:** A small C program that opens a file, writes bytes to it, and closes it cleanly.

**What it teaches you:**
- `fopen()`, `fwrite()`, `fclose()` — the core of any upload server
- Error handling with `perror()` and `errno`
- Working with binary vs text mode (`"wb"` vs `"w"`)
- Creating directories with `mkdir()`

**Why it matters:** Your server's entire job is writing uploaded bytes to disk. If you can't do this reliably, nothing else matters. Master this first.

**Connects to the final project:** The `uploads/` folder storage step is 100% this skill.

---

## 2. Struct-Based Message/Metadata Model

**What it is:** A `struct` that represents a file upload request — filename, file size, content type.

**What it teaches you:**
- Defining and using `struct` types
- Working with fixed-size char arrays (`char filename[256]`)
- Passing structs to functions by pointer
- Printing structured data with `printf`

**Why it matters:** Before you can parse HTTP-like headers from a client, you need a clean data model to store what you parsed. This struct becomes the backbone of your server's request handling.

**Connects to the final project:** The `Filename` and `Content-Length` headers map directly to fields in this struct.

---

## 3. Buffer & String Parser

**What it is:** A program that reads a raw string like `"Filename: test.txt\nContent-Length: 512"` and extracts the values from it.

**What it teaches you:**
- `sscanf()`, `strstr()`, `strtok()`, `strcpy()`
- Pointer arithmetic on strings
- Safe string handling (avoiding buffer overflows)
- Writing your own mini-parser

**Why it matters:** When a client sends headers to your server, they arrive as raw text. You need to pull out the filename and size before you can do anything else. This is exactly that logic.

**Connects to the final project:** This becomes your HTTP-like header parser in the server.

---

## 4. Simple CLI File Copier

**What it is:** A command-line tool that reads a file from one path and writes it to another — like a manual `cp` command.

**What it teaches you:**
- Reading files in chunks with a buffer (`char buf[4096]`)
- Looping with `fread()` / `fwrite()` until EOF
- Handling partial reads and writes correctly
- Command-line arguments with `argc` / `argv`

**Why it matters:** Your upload server receives file bytes over a socket in chunks — not all at once. This teaches you the exact read-loop pattern you'll reuse for receiving file data from clients.

**Connects to the final project:** The "receive bytes → write to disk" loop in your server is this, just with a socket instead of a file as the source.

---

## 5. In-Memory Upload Log

**What it is:** A program that tracks uploaded files using an array of structs — storing filename, size, and a timestamp string for each upload.

**What it teaches you:**
- Arrays of structs
- Simple CRUD logic in C (add, list, search by name)
- Formatting output with `printf` and `sprintf`
- Understanding state management before introducing sockets

**Why it matters:** Before your server handles multiple connections, you need to think about how it tracks what's been uploaded. This is that logic in isolation — without network complexity getting in the way.

**Connects to the final project:** This becomes your server's upload registry, later extended with thread safety when you learn concurrency.

---

## 6. Response Builder

**What it is:** A function that constructs a HTTP-like response string — status line, headers, and body — into a char buffer.

**What it teaches you:**
- `snprintf()` for safe string building
- Designing reusable functions with clear inputs/outputs
- Understanding what an HTTP response actually looks like as raw text
- Separating concerns (building a response vs sending it)

**Why it matters:** Your server needs to send back a "200 OK — upload successful" (or an error) to every client. Writing the response builder now means when you learn sockets, you only need to add one line: `send(socket, response, len, 0)`.

**Connects to the final project:** This is the last step in your server's flow — the response that confirms upload success.

---

## 🚀 Why This Approach Works

### Immediate Progress
You can start coding today. No sockets, no Makefiles, no GDB needed yet — just GCC and a terminal.

### Solid Foundation
Each piece you build now maps 1:1 to a component in your final server. You're not doing busywork — you're pre-building the server in safe, isolated chunks.

### Understanding Before Complexity
You'll understand *what* your server does at every step before the complexity of POSIX sockets makes it hard to see the logic underneath.

### Easy Transition
| What you build now | What it becomes later |
|---|---|
| File Writer Utility | `uploads/` folder handler in your server |
| Metadata Struct | Your request parser's data model |
| String Parser | HTTP-like header parser |
| File Copier (chunk loop) | Socket receive → disk write loop |
| Upload Log | Server's in-memory file registry |
| Response Builder | `send()` payload constructor |

### Testable Without a Network
Every program here runs standalone. You can test, break, and fix things without spinning up a server or a client.
