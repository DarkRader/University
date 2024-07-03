<h1>Phone Directory</h1>

<td class="lrtbCell" colspan="3" align="left">
  <p>The COVID-19 pandemic is once again getting out of control, so stricter measures are needed. To improve contact tracing, the state is legally allowed direct access to the phone directories of tracked citizens. Your task is to write a program that simplifies searching for contacts in these phone directories and generates the necessary reports.</p>
  <p>Your task is to implement the following function:</p>
  <pre><code>bool report ( const string &amp; fileName, ostream &amp; out );</code></pre>
  <ul>
    <li><code>fileName</code> is a string containing the path to the phone directory and queries,</li>
    <li><code>out</code> is the output stream where the report should be written,</li>
    <li>the return value of the function is <code>false</code> if an error occurs while processing the file or the phone directory within it, or <code>true</code> if the processing completes successfully.</li>
  </ul>
  <p>The input file first contains the phone directory entries. A blank line follows, then a list of queries to which your program must respond and write the answers to the provided output stream. Each phone directory entry is on a new line and contains the first name, last name, and phone number. Each item is separated by any number of whitespace characters (excluding newlines). The subsequent queries always contain just one word.</p>
  <p>The function searches for entries that match the full first name, last name, or both. Partial matches like "Joh" and "John" are not accepted. Matching entries should be printed to the provided stream, and the order of output should match the order in the phone directory. All outputs should be displayed on the provided output stream (not on the standard output <code>cout</code> or error output <code>cerr</code>).</p>
  <p>The format of the input and output can be seen in the example of the function's operation below. If the input is invalid, the function must detect this and return <code>false</code>. Consider the input invalid if:</p>
  <ul>
    <li>an attribute is missing or there are too many attributes,</li>
    <li>the phone number does not have exactly nine digits,</li>
    <li>the phone number contains characters other than digits,</li>
    <li>the phone number starts with 0,</li>
    <li>there is any additional input after the phone number on the line (whitespace characters may follow, but nothing else),</li>
    <li>the blank line after the list of numbers is missing.</li>
  </ul>
  <hr />
  <p><strong>Notes:</strong>
  <ul>
    <li>The attached archive contains sample program runs and test inputs.</li>
    <li>The newline character (\n) is also present after the last line of output (including any error message).</li>
    <li>If you wish, you can use <code>std::string</code>, <code>std::vector</code>, <code>std::array</code>, and algorithms from the C++ Standard Library <code>algorithm</code>. Alternatively, you can use dynamically allocated arrays.</li>
    <li>To complete the task, it might be useful to use <code>std::getline</code> and/or <code>std::stringstream</code>.</li>
    <li>The task focuses on file handling, so you do not need to worry too much about time or memory constraints.</li>
    <li><strong>Update 8.3.2023:</strong> Do not use the <code>std::ws</code> manipulator, as it may not work as expected given the compiler version in the Progtest system. It should not be needed to solve the task.</li>
  </ul>
  </p>
</td>