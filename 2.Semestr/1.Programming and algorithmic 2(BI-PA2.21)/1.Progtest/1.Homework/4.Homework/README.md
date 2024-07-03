
<h1>File with Versions</h1>


<tr>
        <td>
            <p>The task is to design and implement a class <tt>CFile</tt> that will simulate a binary file.</p>

<p>The required class will meet the interface according to the example below. The requirements are
                read and write operations, setting the pointer position, and truncating the file. Additionally,
                the class should be able to remember file versions. The interface includes a method that archives
                the current content of the file. It will then be possible to revert to this version of the file.
                Many such versions of the content can be created (the implicit limit is only the available memory
                size), and it will be possible to return to any older version (the "undo" principle). It is assumed
                that the stored data is written to the operating memory (not to the disk, the class only simulates
                file behavior).</p>

<p>For backup reasons, we want to be able to create copies of an existing <tt>CFile</tt> instance.
                Copies will be created both by the copy constructor and by the = operator. The resulting copies
                must be identical independent objects, meaning operations with one of them cannot affect the content
                of the other. On the other hand, it can be assumed that there will not be many changes between copies,
                so some data can be shared in the interest of saving space. Copying creates an identical object,
                meaning stored versions of the content are also transferred.</p>

<p>The required interface of the class:</p>

<dl>
                <dt>constructor</dt>
                <dd>The default constructor creates an empty instance of the file (size 0 B, position in the file 0).</dd>
                
<dt>destructor, op= and copy constructor</dt>
<dd>implement if the automatically generated variant is not suitable,</dd>
                
<dt>write(data, len)</dt>
                <dd>This method writes the given data block (<tt>data</tt>) of length <tt>len</tt> at the current position. 
                    The current position in the file is moved behind the last written byte after the write. The <tt>write</tt>
                    method overwrites data (if the current position is inside the file) or extends the file size. 
                    The return value is the number of bytes written.</dd>
                
<dt>read(data, len)</dt>
                <dd>This method reads the required number of bytes (<tt>len</tt>) into the <tt>data</tt> array. 
                    The return value is the number of bytes read (it can be less than <tt>len</tt> depending on the 
                    current position in the file). The method also moves the current position in the file forward by 
                    the number of bytes read.</dd>
                
<dt>seek(pos)</dt>
                <dd>This method moves the current position in the file to the <tt>pos</tt> position. 
                    The position is used for subsequent read/write operations. 
                    The <tt>pos</tt> parameter must be in the range of 0 to the file length (both bounds inclusive). 
                    The return value is <tt>true</tt> for success, <tt>false</tt> for failure (position out of bounds).</dd>
                
<dt>truncate()</dt>
                <dd>This method truncates the file to the size given by the current position in the file.</dd>
                
<dt>fileSize()</dt>
                <dd>This method returns the current size of the file in bytes.</dd>
                
<dt>addVersion()</dt>
                <dd>This method archives the current content of the file and the current position in the file 
                    (creates a version). This version will be stored in the <tt>CFile</tt> instance.</dd>
                
<dt>undoVersion()</dt>
                <dd>This method returns the file content and the current position in the file to the state they were 
                    in at the corresponding previous call to <tt>addVersion</tt>. It is possible to return to previous 
                    versions multiple times, as long as there are previous archived versions. 
                    Calling <tt>undoVersion</tt> returns <tt>true</tt> for success, <tt>false</tt> for failure 
                    (no previous version exists).</dd>
            </dl>

<hr />

<p>Submit a file that contains the implemented <tt>CFile</tt> class. The class must meet the public
                interface as described - if your submitted solution does not include the described interface, 
                a compilation error will occur. However, you can add other methods (public or private) 
                and member variables to the class. The submitted file must include both the class declaration 
                (interface description) and the definitions of methods, the constructor, and the destructor. 
                It does not matter whether the methods are implemented inline or separately. 
                The submitted file must not contain any header file inclusions and the <tt>main</tt> function 
                (the <tt>main</tt> function and header file inclusions can remain but must be wrapped with 
                conditional compilation directives as shown below).</p>

<p>The class is tested in a limited environment, where the available memory is limited (sufficient 
                to store the list) and the runtime is limited. For solving, you do not have access to the STL 
                or <tt>std::string</tt>. The task is intended to practice understanding deep and shallow copying.
                Using the STL would not fulfill this goal.</p>

<p>The required public interface of the class and a usage example are in the attached archive.</p>

<b>Notes:</b>
            <ul>
                <li>Assessment is divided between mandatory, optional, and bonus tests. 
                    To pass the mandatory tests, a basic version of content copying is sufficient.</li>

<li>To pass the additional tests, it is necessary to effectively share parts of the data so that 
                    the resulting copies take up a reasonable amount of memory. You can assume that changes between 
                    versions and changes between instance copies are small. Thus, immutable parts can be shared 
                    using reference counting and copy-on-write techniques.</li>

<li>In the optional test, <tt>CFile</tt> instances are copied, and content versions are created, 
                    but the total number of different content versions is low. Therefore, it is enough to consider 
                    reference counting for entire versions of file contents.</li>

<li>In the bonus test, files are intensively changed after being copied, and many different file 
                    versions are created. To save memory, it is necessary to use reference counting and 
                    copy-on-write for versions or parts of files.</li>

<li>A solution that passes the mandatory and optional tests with 100% can be used for code review 
                    (it is not necessary to pass the bonus test for code review).</li>
            </ul>
        </td>
    </tr>