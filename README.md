<h1>Simple UNIX-Style Shell in C</h1>


<p>This repository contains a simple UNIX-style shell implemented in C. The shell project explores various aspects of system programming, including process management, file operations, and system calls.</p>


<h2>Key Concepts</h2>

<ul>

<li>The history of the UNIX operating system, including its original designers and implementers.</li>

<li>The first version of the UNIX shell.</li>

<li>The relationship between the B programming language (a predecessor to C) and UNIX.</li>

<li>Ken Thompson, one of the notable figures in UNIX's development.</li>

<li>How a shell works, including process creation and management.</li>

<li>Understanding process IDs (PID) and parent process IDs (PPID).</li>

<li>Environment variable manipulation in the current process.</li>

<li>The difference between functions and system calls.</li>

<li>Process creation using <code>fork()</code>.</li>

<li>The three prototypes of <code>main()</code>.</li>

<li>How the shell uses the <code>PATH</code> environment variable to locate programs.</li>

<li>Executing another program with the <code>execve</code> system call.</li>

<li>Suspending process execution until a child process terminates.</li>

<li>Understanding EOF (end-of-file) in I/O operations.</li>

</ul>


<h2>Functions Used</h2>

<table border="1">

<tr>

<th>Function/SysCalls</th>

<th>Description</th>

</tr>

<tr>

<td><code>access (man 2 access)</code></td>

<td>Check if a file or directory can be accessed with the specified permissions.</td>

</tr>

<tr>

<td><code>chdir (man 2 chdir)</code></td>

<td>Change the current working directory of the process.</td>

</tr>

<tr>

<td><code>close (man 2 close)</code></td>

<td>Close a file descriptor or file stream.</td>

</tr>

<tr>

<td><code>closedir (man 3 closedir)</code></td>

<td>Close a directory stream opened with <code>opendir</code>.</td>

</tr>

<tr>

<td><code>execve (man 2 execve)</code></td>

<td>Execute a program with the provided arguments.</td>

</tr>

<tr>

<td><code>exit (man 3 exit)</code></td>

<td>Terminate the calling process with an exit status.</td>

</tr>

<tr>

<td><code>_exit (man 2 _exit)</code></td>

<td>Terminate the calling process immediately without cleanup.</td>

</tr>

<tr>

<td><code>fflush (man 3 fflush)</code></td>

<td>Flush buffered data to a file stream.</td>

</tr>

<tr>

<td><code>fork (man 2 fork)</code></td>

<td>Create a new process (child) by duplicating the existing process (parent).</td>

</tr>

<tr>

<td><code>free (man 3 free)</code></td>

<td>Deallocate memory previously allocated with <code>malloc</code> or related functions.</td>

</tr>

<tr>

<td><code>getcwd (man 3 getcwd)</code></td>

<td>Get the current working directory of the process.</td>

</tr>

<tr>

<td><code>getline (man 3 getline)</code></td>

<td>Read a line from a file stream or buffer.</td>

</tr>

<tr>

<td><code>getpid (man 2 getpid)</code></td>

<td>Get the process ID (PID) of the current process.</td>

</tr>

<tr>

<td><code>isatty (man 3 isatty)</code></td>

<td>Check if a file descriptor refers to a terminal.</td>

</tr>

<tr>

<td><code>kill (man 2 kill)</code></td>

<td>Send a signal to a process or a group of processes.</td>

</tr>

<tr>

<td><code>malloc (man 3 malloc)</code></td>

<td>Allocate memory on the heap for dynamic data storage.</td>

</tr>

<tr>

<td><code>open (man 2 open)</code></td>

<td>Open a file or create it if it does not exist, returning a file descriptor.</td>

</tr>

<tr>

<td><code>opendir (man 3 opendir)</code></td>

<td>Open a directory for reading, returning a directory stream.</td>

</tr>

<tr>

<td><code>perror (man 3 perror)</code></td>

<td>Print a system error message to the standard error stream.</td>

</tr>

<tr>

<td><code>read (man 2 read)</code></td>

<td>Read data from a file descriptor into a buffer.</td>

</tr>

<tr>

<td><code>readdir (man 3 readdir)</code></td>

<td>Read the next entry from a directory stream.</td>

</tr>

<tr>

<td><code>signal (man 2 signal)</code></td>

<td>Set a signal handler function for a specific signal.</td>

</tr>

<tr>

<td><code>stat (__xstat) (man 2 stat)</code></td>

<td>Get file status information for a specified file or directory.</td>

</tr>

<tr>

<td><code>lstat (__lxstat) (man 2 lstat)</code></td>

<td>Get symbolic link file status information for a specified file or directory.</td>

</tr>

<tr>

<td><code>fstat (__fxstat) (man 2 fstat)</code></td>

<td>Get file status information for a specified file descriptor.</td>

</tr>

<tr>

<td><code>strtok (man 3 strtok)</code></td>

<td>Tokenize a string by splitting it into smaller strings based on a delimiter.</td>

</tr>

<tr>

<td><code>wait (man 2 wait)</code></td>

<td>Wait for the child process to terminate and collect its exit status.</td>

</tr>

<tr>

<td><code>waitpid (man 2 waitpid)</code></td>

<td>Wait for a specific child process to terminate and collect its exit status.</td>

</tr>

<tr>

<td><code>wait3 (man 2 wait3)</code></td>

<td>Obsolete version of <code>wait</code> with more options for collecting exit status.</td>

</tr>

<tr>

<td><code>wait4 (man 2 wait4)</code></td>

<td>Obsolete version of <code>waitpid</code> with more options for collecting exit status.</td>

</tr>

<tr>

<td><code>write (man 2 write)</code></td>

<td>Write data from a buffer to a file descriptor.</td>

</tr>

</table>



<h2>How to Build and Run</h2>

<ol>

<li>Clone this repository to your local machine.</li>

<li>Open a terminal and navigate to the project directory.</li>

<li>Compile the C source files using a C compiler (e.g., GCC):</li>

</ol>

<pre><code>gcc -o myshell *.c</code></pre>

<ol start="4">

<li>Run the shell:</li>

</ol>

<pre><code>./hsh</code></pre>



<p>Now, you can interact with the simple UNIX-style shell in your terminal.</p>



<h2>References</h2>

<p>For more information on the concepts and functions used in this project, you can refer to the corresponding manual pages in your UNIX-like operating system by running <code>man</code> followed by the function name (e.g., <code>man 2 execve</code>).</p>
