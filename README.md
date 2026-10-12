# 📂 File Upload API (C# + ASP.NET Core)

## Overview

A file upload API built with C# and ASP.NET Core that allows clients to upload files over HTTP, stores uploaded files, and returns upload status. The project begins with C# fundamentals and gradually introduces networking, file handling, authentication, databases, and cloud storage.

The final goal is to build the file-upload service for **SOARS**, a personal library for saving, organizing, archiving, and sharing links, files, and notes in one clean, searchable workspace.

## Tech Stack

- C# and .NET SDK
- ASP.NET Core Minimal APIs
- `System.IO` for file operations
- PostgreSQL with Npgsql
- AWS S3 for object storage (later stage)

## Features

- Accept file upload requests over HTTP.
- Receive file metadata and content.
- Store uploaded files in a local `uploads/` directory.
- Validate file names, file sizes, and file types.
- Return appropriate HTTP status codes.
- Track uploaded files and their metadata in PostgreSQL.
- Authenticate users using Supabase Auth.
- Enforce file ownership and storage quotas.
- Support cloud storage with AWS S3.

---

## 🛠️ Suggested Learning Path

### Stage 1: C# File Writer Utility

**What it is:** A small console application that creates a file and writes text or binary data to disk.

**What it teaches you:**
- `File`, `FileStream`, and the `System.IO` namespace.
- Creating, reading, writing, and deleting files.
- Handling exceptions with `try`, `catch`, and `finally`.
- Understanding paths, directories, and file permissions.
- Using asynchronous file operations.

**Why it matters:** File uploads ultimately require reliable storage of incoming file contents.

**Connects to the final project:** This becomes the local file-storage component of the upload API.

### Stage 2: Struct-Based Metadata Model

**What it is:** Create a C# class or record representing an uploaded file.

**What it teaches you:**
- Classes, records, properties, and constructors.
- Strings, numeric types, and `DateTimeOffset`.
- Object initialization and validation.
- Separating data models from application logic.

**Example model:**

```csharp
public class UploadMetadata
{
    public string FileName { get; set; } = "";
    public long SizeBytes { get; set; }
    public string ContentType { get; set; } = "";
    public DateTimeOffset UploadedAt { get; set; }
}
```

**Why it matters:** Every upload needs metadata to identify and organize the stored file.

**Connects to the final project:** This model will eventually represent file metadata stored in PostgreSQL.

### Stage 3: Metadata and Request Validation

**What it is:** Build a program that receives file metadata and validates it before accepting an upload.

**What it teaches you:**
- String manipulation and parsing.
- Conditional statements and validation methods.
- Exception handling.
- Safe filename generation.
- Validating file sizes and allowed extensions.

**Why it matters:** Client-supplied filenames, sizes, and content types cannot be trusted.

**Connects to the final project:** This becomes the validation layer for incoming upload requests.

### Stage 4: File Copier and Stream Processing

**What it is:** Build a command-line utility that copies a file from one location to another using streams.

**What it teaches you:**
- `FileStream`, `Stream`, and `CopyToAsync()`.
- Reading and writing data in chunks.
- Asynchronous programming with `async` and `await`.
- Handling I/O errors and incomplete operations.
- Managing streams and disposing of resources.

**Why it matters:** Large files should be processed without loading their entire contents into memory.

**Connects to the final project:** The same stream-processing concepts are used when receiving uploaded file contents and writing them to storage.

### Stage 5: In-Memory Upload Registry

**What it is:** Create a console application that tracks uploaded files using a `List<UploadMetadata>`.

**What it teaches you:**
- Collections and generic lists.
- Searching, adding, updating, and removing records.
- LINQ for filtering and sorting.
- Generating unique file identifiers.
- Separating business logic into reusable classes.

**Why it matters:** The server needs to keep track of files and their metadata.

**Connects to the final project:** This registry will later be replaced by PostgreSQL so metadata persists after the application restarts.

### Stage 6: HTTP Response Builder and Minimal API

**What it is:** Create an ASP.NET Core Minimal API with endpoints that return appropriate HTTP responses.

**What it teaches you:**
- The .NET SDK and project structure.
- HTTP methods, routes, headers, and status codes.
- JSON serialization.
- Request validation and error responses.
- Testing endpoints with an API client.

**Example endpoints:**

- `GET /` — Check server status.
- `POST /upload` — Upload a file.
- `GET /files` — List uploaded files.
- `GET /files/{id}` — Retrieve file metadata.

**Why it matters:** ASP.NET Core handles HTTP networking and request parsing, so you do not need to implement HTTP manually using raw TCP sockets.

**Connects to the final project:** This becomes the foundation of the upload server.

---

## 🚀 Advanced Stages: Turning It Into a Real API

### Stage 7: File Upload Endpoint

**What it is:** Implement `POST /upload` using ASP.NET Core and `IFormFile`.

**What it teaches you:**
- Receiving multipart/form-data requests.
- Handling uploaded files using `IFormFile`.
- Streaming files to disk.
- Setting maximum request and file sizes.
- Returning HTTP success and error responses.
- Testing uploads with Postman or another API client.

**Connects to SOARS:** Users can upload files through the frontend.

### Stage 8: PostgreSQL and Npgsql

**What it is:** Replace the in-memory registry with a PostgreSQL database.

**What it teaches you:**
- Relational database design.
- Tables, primary keys, foreign keys, and indexes.
- SQL queries and parameterized commands.
- Connecting C# to PostgreSQL using Npgsql.
- Persisting file metadata and tracking storage usage.

**Connects to SOARS:** The database stores file metadata, ownership, notes, links, tags, and other searchable information.

### Stage 9: Authentication and Authorization

**What it is:** Integrate Supabase Auth with the C# API.

**What it teaches you:**
- Authentication versus authorization.
- Access tokens and JWT validation.
- Protecting API endpoints.
- Associating uploaded files with authenticated users.
- Enforcing ownership and sharing permissions.
- Validating access before allowing downloads or deletions.

**Connects to SOARS:** Each user gets a private library with controlled sharing.

### Stage 10: Storage Quotas and File Management

**What it is:** Add per-user storage limits and file-management operations.

**What it teaches you:**
- Calculating total storage usage.
- Enforcing upload limits.
- Updating and deleting file metadata safely.
- Handling partial failures between disk storage and database operations.
- Preventing unauthorized access to other users' files.

**Connects to SOARS:** Users can manage their libraries without exceeding their storage allowances.

### Stage 11: AWS S3 Object Storage

**What it is:** Replace or supplement local file storage with Amazon S3.

**What it teaches you:**
- S3 buckets and objects.
- AWS SDK for .NET.
- Uploading, downloading, and deleting objects.
- Configuring credentials securely.
- Presigned URLs and private file access.
- Understanding multipart uploads for large files.

**Connects to SOARS:** Files can be stored in cloud object storage instead of relying on a server's local disk.

---

## 📁 Suggested Project Structure

```text
Soars.UploadApi/
├── Program.cs
├── Models/
│   └── UploadMetadata.cs
├── Services/
│   ├── FileStorageService.cs
│   └── UploadService.cs
├── Data/
│   └── DatabaseService.cs
├── Endpoints/
│   └── UploadEndpoints.cs
├── uploads/
├── appsettings.json
├── .gitignore
└── Soars.UploadApi.csproj
```

Keep credentials and secrets out of source control. The `uploads/` directory should be ignored by Git.

## 🚀 Final Project Flow

1. The server starts and exposes HTTP endpoints.
2. A user authenticates through Supabase Auth.
3. The client sends a file and its metadata to the upload endpoint.
4. The API validates the user's access and the upload constraints.
5. The file is stored on disk or in AWS S3.
6. Its metadata and ownership are saved in PostgreSQL.
7. The API returns the upload status and file identifier.
8. Subsequent requests verify authorization before accessing the file.

## 🎯 Learning Strategy

Build and test each stage independently before moving to the next. Start with local file storage and an unauthenticated development API. Add PostgreSQL, authentication, quotas, and cloud storage only after the basic upload flow works.

The objective is to understand how the components work together, rather than simply assembling a collection of libraries.