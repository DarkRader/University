<h1>Hybrid Encryption</h1>

<td class="lrtbCell" colspan="3" align="left"><p>Your task is to implement two functions (<code>seal</code> and <code>open</code>) for encrypting/decrypting data using hybrid encryption.</p>
<p>Parameters for the <code>seal</code> function you will implement:</p>
<pre>
bool seal(string_view inFile, string_view outFile, string_view publicKeyFile, string_view symmetricCipher)
</pre>
<ul>
<li><code>inFile</code> - file containing binary data to be encrypted,</li>
<li><code>outFile</code> - output file where all necessary decryption information will be stored,</li>
<li><code>publicKeyFile</code> - public key used for encrypting the symmetric key,</li>
<li><code>symmetricCipher</code> - name of the symmetric cipher used for encryption,</li>
<li>returns <code>true</code> on success, <code>false</code> otherwise. If the function fails, ensure that the <code>outFile</code> does not exist.</li>
</ul>
<p>The function generates a symmetric key and an initialization vector (IV) which will be used with the <code>symmetricCipher</code>. Using this cipher, key, and IV, the function encrypts the data in <code>inFile</code>. The symmetric key is encrypted using asymmetric encryption (RSA) with the public key stored in <code>publicKeyFile</code>.</p>
<p>OpenSSL does most of the work for you:</p>
<ul>
<li><code>PEM_read_PUBKEY</code> - reads the public key,</li>
<li><code>EVP_SealInit</code> - generates a shared key and IV (if necessary), encrypts the shared key, and sets up the context,</li>
<li><code>EVP_SealUpdate</code> and <code>EVP_SealFinal</code> function similarly to previous tasks.</li>
</ul>
<p>Hybrid encryption considers encrypting for multiple recipients. Data is encrypted once with a shared key and IV, but the shared key can be encrypted with multiple public keys. Therefore, the function accepts an array of public keys.</p>
<p>The output file will have the following structure:</p>
<style type="text/css">
#headerFileTable{
    border-collapse: collapse;
}
#headerFileTable th, #headerFileTable td {
  border: 1px solid black;
  padding: 8px;
}
</style>
<table id="headerFileTable">
<thead>
    <tr>
        <th>Position in File</th>
        <th>Length</th>
        <th>Structure</th>
        <th>Description</th>
    </tr>
</thead>
<tbody>
    <tr>
        <td>0</td>
        <td>4 B</td>
        <td>int</td>
        <td>NID - numerical identifier for an OpenSSL cipher. (Used symmetric cipher)</td>
    </tr>
    <tr>
        <td>4</td>
        <td>4 B</td>
        <td>int</td>
        <td><code>EKlen</code> - length of the encrypted key</td>
    </tr>
    <tr>
        <td>8</td>
        <td><code>EKlen</code> B</td>
        <td>unsigned char array</td>
        <td>Encrypted key using RSA</td>
    </tr>
    <tr>
        <td>8 + <code>EKlen</code></td>
        <td><code>IVlen</code> B</td>
        <td>unsigned char array</td>
        <td>Initialization vector (if necessary)</td>
    </tr>
    <tr>
        <td>8 + <code>EKlen</code> + <code>IVlen</code></td>
        <td>—</td>
        <td>unsigned char array</td>
        <td>Encrypted data</td>
    </tr>
</tbody>
</table>
<p>
<hr/>
<p>Parameters for the <code>open</code> function you will implement:</p>
<pre>
bool open(string_view inFile, string_view outFile, string_view privateKeyFile)
</pre>
<ul>
<li><code>inFile</code> - encrypted file in the same format as the output file from the <code>seal</code> function,</li>
<li><code>outFile</code> - output file where all decrypted data will be stored (binary match expected with the input file to the <code>seal</code> function),</li>
<li><code>privateKeyFile</code> - private key used for decrypting the encrypted key,</li>
<li>returns <code>true</code> on success, <code>false</code> otherwise. If the function fails, ensure that the <code>outFile</code> does not exist.</li>
</ul>
<p>The main functions to be used in this function are <code>PEM_read_PrivateKey</code>, <code>EVP_OpenInit</code>, <code>EVP_OpenUpdate</code>, and <code>EVP_OpenFinal</code>.</p>
<hr/>
<p><strong>Contents of sample data:</strong></p>
<ul>
<li><code>PublicKey.pem</code> - public key (try to open it as text),</li>
<li><code>PrivateKey.pem</code> - private key,</li>
<li><code>sample.cpp</code> - file with declarations and basic test,</li>
<li><code>sealed_sample.bin</code> - encrypted file to test decryption. It was encrypted with the provided public key, and after decryption, you will find ASCII text in it. If you encrypt the same data, the file will not match <code>sealed_sample.bin</code> because a different key and IV were used.</li>
</ul>
<p><strong>Final Notes:</strong></p>
<ul>
<li>There are many places where functions can return errors in this task. Thoroughly check and consider using object-oriented design and automatic resource management using <code>unique_ptr</code> (applies to context, key, allocated arrays, and file closing).</li>
<li>The length of the encrypted key depends on the public key. You cannot assume a fixed length.</li>
<li>During compilation, remember to link the OpenSSL crypto library using <code>-lcrypto</code>.</li>
<li>The version of OpenSSL on Progtest is 3.0.11.</li>
<li>All "notes" from the previous task also apply.</li>
</ul>
</td>