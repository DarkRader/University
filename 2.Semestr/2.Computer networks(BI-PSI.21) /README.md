<h1>Homework - TCP server</h1>

<section class="doc-section level-1"><h2 id="_annotation"><a class="anchor" href="#_annotation" aria-hidden="true"></a>Annotation</h2><p>The task is to create multithreaded server for TCP/IP communication and implement communication protocol according to the specification. Note, the implementation of the client part is not a part of this task. See the section Testing</a>.</p>

<section class="doc-section level-1"><h2 id="_task"><a class="anchor" href="#_task" aria-hidden="true"></a>Task</h2><p>Create a server for automatic control of remote robots. Robots authenticate to the server and server directs them to origing of the coordinate system. For testing purposes each robot starts at the random coordinates and its target location is always located on the coordinate [0,0]. The robot should reach that target coordinate and pick the secret message, which can be found only on that spot. Server is able to navigate several robots at once and implements communication protocol without errors.</p></section>
<section class="doc-section level-1"><h2 id="_detailed-specification"><a class="anchor" href="#_detailed-specification" aria-hidden="true"></a>Detailed specification</h2><p>Communication between server and robots is implemented via a pure textual protocol. Each command ends with a pair of special symbols "\a\b". Server must follow the communication protocol strictly, but should take into account imperfect robots firmware (see section Special situations).</p>
<p>Server messages:</p>
  
  <div class="table-block"><table class="frame-all grid-all"><colgroup><col><col><col></colgroup><tbody><tr><th class="halign-left valign-top">Name</th><th class="halign-left valign-top">Message</th><th class="halign-left valign-top">Description</th></tr><tr><td class="halign-left valign-top">SERVER_CONFIRMATION</td><td class="halign-left valign-top">&lt;16-bit number in decimal notation&gt;\a\b</td><td class="halign-left valign-top">Message with confirmation code. Can contain maximally 5 digits and the termination sequence \a\b.</td></tr><tr><td class="halign-left valign-top">SERVER_MOVE</td><td class="halign-left valign-top">102 MOVE\a\b</td><td class="halign-left valign-top">Command to move one position forward</td></tr><tr><td class="halign-left valign-top">SERVER_TURN_LEFT</td><td class="halign-left valign-top">103 TURN LEFT\a\b</td><td class="halign-left valign-top">Command to turn left</td></tr><tr><td class="halign-left valign-top">SERVER_TURN_RIGHT</td><td class="halign-left valign-top">104 TURN RIGHT\a\b</td><td class="halign-left valign-top">Command to turn right</td></tr><tr><td class="halign-left valign-top">SERVER_PICK_UP</td><td class="halign-left valign-top">105 GET MESSAGE\a\b</td><td class="halign-left valign-top">Command to pick up the message</td></tr><tr><td class="halign-left valign-top">SERVER_LOGOUT</td><td class="halign-left valign-top">106 LOGOUT\a\b</td><td class="halign-left valign-top">Command to terminate the connection after successfull message discovery</td></tr><tr><td class="halign-left valign-top">SERVER_KEY_REQUEST</td><td class="halign-left valign-top">107 KEY REQUEST\a\b</td><td class="halign-left valign-top">Command to request Key ID for the communication</td></tr><tr><td class="halign-left valign-top">SERVER_OK</td><td class="halign-left valign-top">200 OK\a\b</td><td class="halign-left valign-top">Positive acknowledgement</td></tr><tr><td class="halign-left valign-top">SERVER_LOGIN_FAILED</td><td class="halign-left valign-top">300 LOGIN FAILED\a\b</td><td class="halign-left valign-top">Autentication failed</td></tr><tr><td class="halign-left valign-top">SERVER_SYNTAX_ERROR</td><td class="halign-left valign-top">301 SYNTAX ERROR\a\b</td><td class="halign-left valign-top">Incorrect syntax of the message</td></tr><tr><td class="halign-left valign-top">SERVER_LOGIC_ERROR</td><td class="halign-left valign-top">302 LOGIC ERROR\a\b</td><td class="halign-left valign-top">Message sent in wrong situation</td></tr><tr><td class="halign-left valign-top">SERVER_KEY_OUT_OF_RANGE_ERROR</td><td class="halign-left valign-top">303 KEY OUT OF RANGE\a\b</td><td class="halign-left valign-top">Key ID is not in the expected range</td></tr></tbody></table></div>
<p>Client messages:</p>
<div class="table-block"><table class="frame-all grid-all"><colgroup><col><col><col><col><col></colgroup><tbody><tr><th class="halign-left valign-top">Name</th><th class="halign-left valign-top">Message</th><th class="halign-left valign-top">Description</th><th class="halign-left valign-top">Example</th><th class="halign-left valign-top">Maximal length</th></tr><tr><td class="halign-left valign-top">CLIENT_USERNAME</td><td class="halign-left valign-top">&lt;user name&gt;\a\b</td><td class="halign-left valign-top">Message with username. Username can be any sequence of characters except for the pair \a\b.</td><td class="halign-left valign-top">Oompa_Loompa\a\b</td><td class="halign-left valign-top">20</td></tr><tr><td class="halign-left valign-top">CLIENT_KEY_ID</td><td class="halign-left valign-top">&lt;Key ID&gt;\a\b</td><td class="halign-left valign-top">Message with Key ID. Can contain an integer with maximum of three ciphers.</td><td class="halign-left valign-top">2\a\b</td><td class="halign-left valign-top">5</td></tr><tr><td class="halign-left valign-top">CLIENT_CONFIRMATION</td><td class="halign-left valign-top">&lt;16-bit number in decimal notation&gt;\a\b</td><td class="halign-left valign-top">Message with confirmation code. Can contain maximally 5 digits and the termination sequence \a\b.</td><td class="halign-left valign-top">1009\a\b</td><td class="halign-left valign-top">7</td></tr><tr><td class="halign-left valign-top">CLIENT_OK</td><td class="halign-left valign-top">OK &lt;x&gt; &lt;y&gt;\a\b</td><td class="halign-left valign-top">Confirmation of performed movement, where <em>x</em> and <em>y</em> are the robot coordinates after execution of move command.</td><td class="halign-left valign-top">OK -3 -1\a\b</td><td class="halign-left valign-top">12</td></tr><tr><td class="halign-left valign-top">CLIENT_RECHARGING</td><td class="halign-left valign-top">RECHARGING\a\b</td><td class="halign-left valign-top">Robot starts charging and stops to respond to messages.</td><td class="halign-left valign-top"></td><td class="halign-left valign-top">12</td></tr><tr><td class="halign-left valign-top">CLIENT_FULL_POWER</td><td class="halign-left valign-top">FULL POWER\a\b</td><td class="halign-left valign-top">Robot has recharged and accepts commands again.</td><td class="halign-left valign-top"></td><td class="halign-left valign-top">12</td></tr><tr><td class="halign-left valign-top">CLIENT_MESSAGE</td><td class="halign-left valign-top">&lt;text&gt;\a\b</td><td class="halign-left valign-top">Text of discovered secret message. Can contain any characters except for the termination sequence \a\b.</td><td class="halign-left valign-top">Haf!\a\b</td><td class="halign-left valign-top">100</td></tr></tbody></table></div>
 
<p>Time constants:</p>
<div class="table-block"><table class="frame-all grid-all"><colgroup><col><col><col></colgroup><tbody><tr><th class="halign-left valign-top">Name</th><th class="halign-left valign-top">Value [s]</th><th class="halign-left valign-top">Description</th></tr><tr><td class="halign-left valign-top">TIMEOUT</td><td class="halign-left valign-top">1</td><td class="halign-left valign-top">Server and client wait for the answer from the other side during this interval.</td></tr><tr><td class="halign-left valign-top">TIMEOUT_RECHARGING</td><td class="halign-left valign-top">5</td><td class="halign-left valign-top">Time interval, during which robot has to finish recharging.</td></tr></tbody></table></div>
<p>Communication with robots could be divided into several phases:</p>
<section class="doc-section level-2"><h3 id="_authentication"><a class="anchor" href="#_authentication" aria-hidden="true"></a>Authentication</h3><p>Server and client both know five pairs of authentication keys (these are not public and private keys):</p>
<div class="table-block"><table class="frame-all grid-all stretch"><colgroup><col style="width: 33.3333%;"><col style="width: 33.3333%;"><col style="width: 33.3334%;"></colgroup><tbody><tr><th class="halign-left valign-top">Key ID</th><th class="halign-left valign-top">Server Key</th><th class="halign-left valign-top">Client Key</th></tr><tr><td class="halign-left valign-top">0</td><td class="halign-left valign-top">23019</td><td class="halign-left valign-top">32037</td></tr><tr><td class="halign-left valign-top">1</td><td class="halign-left valign-top">32037</td><td class="halign-left valign-top">29295</td></tr><tr><td class="halign-left valign-top">2</td><td class="halign-left valign-top">18789</td><td class="halign-left valign-top">13603</td></tr><tr><td class="halign-left valign-top">3</td><td class="halign-left valign-top">16443</td><td class="halign-left valign-top">29533</td></tr><tr><td class="halign-left valign-top">4</td><td class="halign-left valign-top">18189</td><td class="halign-left valign-top">21952</td></tr></tbody></table></div>
<p>Each robot starts communictation with sending its username (CLIENT_USERNAME message). Username can be any sequence of up to 18 characters not containing the termination sequence „\a\b“. In the next step the server asks the client for sending Key ID (SERVER_KEY_ID_REQUEST message), which is in fact an id of the server and client keys, which the client wants to use for authentication. The client answers by sending Key ID (CLIENT_KEY_ID message). After these steps the server knows the correct key pair and it can calculate "hash" code from the username of the client by the following formula:</p>
<div class="listing-block"><pre>Username: Meow!

ASCII representation: 77 101 111 119 33

Resulting hash: ((77 + 101 + 111 + 119 + 33) * 1000) % 65536 = 47784</pre></div>
<p>Resulting hash is 16-bit number in decimal notation. The server then adds a server key to the hash, so that if 16-bit capacity is exceeded, the value simply "wraps around" (due to modulo operation):</p>
<div class="listing-block"><pre>(47784 + 54621) % 65536 = 36869</pre></div>
<p>Resulting confirmation code of server is sent to client as text in SERVER_CONFIRM message. Client takes the received code and calculates hash back from it, then compares it with the expected hash value, which he has calculated from the username. If they are equal, client computes the confirmation code of client and sends it back to the server. Calculation of the client confirmation code is simular to the server one, only the client key is used:</p>
<div class="listing-block"><pre>(47784 + 45328) % 65536 = 27576</pre></div>
<p>Client confirmation key is sent to the server in CLIENT_CONFIRMATION message, server calculates hash back from it and compares it with the original hash of the username. If values are equal, server sends message SERVER_OK, otherwise answers with message SERVER_LOGIN_FAILED and terminates the connection. The whole sequence of steps is represented at the following picture:</p>
<div class="listing-block"><pre>Client                  Server
​------------------------------------------
CLIENT_USERNAME     ---&gt;
                    &lt;---    SERVER_KEY_REQUEST
CLIENT_KEY_ID       ---&gt;
                    &lt;---    SERVER_CONFIRMATION
CLIENT_CONFIRMATION ---&gt;
                    &lt;---    SERVER_OK
                              or
                            SERVER_LOGIN_FAILED
                      .
                      .
                      .</pre></div>
<p>Server does not know usernames in advance. Robots can choose any name, but they have to know the list of client and server keys. The key pair ensures two-sided autentication and prevents the autentication process from being compromised by simple eavesdropping of communication.</p></section>
<section class="doc-section level-2"><h3 id="_movement-of-robot-to-the-target-coordinates"><a class="anchor" href="#_movement-of-robot-to-the-target-coordinates" aria-hidden="true"></a>Movement of robot to the target coordinates</h3><p>Robot can move only straight (SERVER_MOVE), but is able to turn right (SERVER_TURN_RIGHT) or left (SERVER_TURN_LEFT). After each move command robot sends confirmation (CLIENT_OK), part of which is actual coordinates of robot. At the beginning of communication robot position is not known to server. Server must find out robot position and orientation (direction) only from robot answers. In order to prevent infinite wandering of robot in space, each robot has a limited number of movements (move forward). The number of turns is not limited. The number of moves should be sufficient for a reasonable robot transfer to the target. Following is a demonstration of communication. The server first moves the robot twice to detect its current state and then guides it towards the target coordinate [0,0].</p>
<div class="listing-block"><pre>Client                  Server
​------------------------------------------
                  .
                  .
                  .
                &lt;---    SERVER_MOVE
                          or
                        SERVER_TURN_LEFT
                          or
                        SERVER_TURN_RIGHT
CLIENT_CONFIRM  ---&gt;
                &lt;---    SERVER_MOVE
                          or
                        SERVER_TURN_LEFT
                          or
                        SERVER_TURN_RIGHT
CLIENT_CONFIRM  ---&gt;
                &lt;---    SERVER_MOVE
                          or
                        SERVER_TURN_LEFT
                          or
                        SERVER_TURN_RIGHT
                  .
                  .
                  .</pre></div>
<p>This part of communication cannot be skipped, robot waits at least one of the movement commands - SERVER_MOVE, SERVER_TURN_LEFT or SERVER_TURN_RIGHT. There is several obstactles on the way to the target coordinate, which must be bypassed by the robots. The obstacle placement follows these rules:</p>
<div class="ulist"><ul><li>The obstacle spans only a single pair of coordinates.</li><li>All neighbouring coordinates around the obstacle are always free, therefore the obstacle can be always bypassed.</li><li>The obstacle is never placed on the target coordinates [0,0].</li><li>If the robot crushes an obstacle (any obstacle) more than 20 times, it brokes down and ends the connection.</li></ul></div>
<p>The obstacle is detected by the fact that robot doesn&#8217;t change it&#8217;s position after SERVER_MOVE command (the CLIENT_OK message contains the same coordinate as it was in the previous step). If the robot doesn&#8217;t move, the number of remaining moves is not decreased, but the number of remaining crashes is decreased by one.</p></section>
<section class="doc-section level-2"><h3 id="_secret-message-discovery"><a class="anchor" href="#_secret-message-discovery" aria-hidden="true"></a>Secret message discovery</h3><p>After the robot reaches the target coordinate [0,0], it attemps to pick up the secret message (SERVER_PICK_UP). If robot receives command to pick up the secret message, but robot is not in the target coordinate [0,0], an autodestruction of robot is initiated and communication with server is abrupted. After the robot picks the secret message, it sends to the server CLIENT_MESSAGE with the secret. The server has to answer with SERVER_LOGOUT. (It is guaranteed, that secret message never matches the message CLIENT_RECHARGING, so if the recharge message is obtained by the server after the pick up command, it always means that robot started to charge.) After that, client and server close the connection. Demo of the secret message picking:</p>
<div class="listing-block"><pre>Client                  Server
​------------------------------------------
                  .
                  .
                  .
                &lt;---    SERVER_PICK_UP
CLIENT_MESSAGE  ---&gt;
                &lt;---    SERVER_LOGOUT</pre></div></section>
<section class="doc-section level-2"><h3 id="_recharging"><a class="anchor" href="#_recharging" aria-hidden="true"></a>Recharging</h3><p>Each robot has a limited power source. If it starts to run out of battery, he notifies the server and then recharges itself from the solar panel. It does not respond to any messages during the charging. When it finishes, it informs the server and continues there, where it left before recharging. If the robot does not stop charging in the time interval TIMEOUT_RECHARGING, the server terminates the connection.</p>
<div class="listing-block"><pre>Client                    Server
​------------------------------------------
CLIENT_USERNAME   ---&gt;
                  &lt;---    SERVER_CONFIRMATION
CLIENT_RECHARGING ---&gt;

      ...

CLIENT_FULL_POWER ---&gt;
CLIENT_OK         ---&gt;
                  &lt;---    SERVER_OK
                            or
                          SERVER_LOGIN_FAILED
                    .
                    .
                    .</pre></div>
<p>Another example:</p>
<div class="listing-block"><pre>Client                  Server
​------------------------------------------
                    .
                    .
                    .
                  &lt;---    SERVER_MOVE
CLIENT_OK         ---&gt;
CLIENT_RECHARGING ---&gt;

      ...

CLIENT_FULL_POWER ---&gt;
                  &lt;---    SERVER_MOVE
CLIENT_OK         ---&gt;
                  .
                  .
                  .</pre></div></section></section>
<section class="doc-section level-1"><h2 id="_error-situations"><a class="anchor" href="#_error-situations" aria-hidden="true"></a>Error situations</h2><p>Some robots can have corrupted firmware and thus communicate wrongly. Server should detect misbehavior and react correctly.</p>
<section class="doc-section level-2"><h3 id="_error-during-authentication"><a class="anchor" href="#_error-during-authentication" aria-hidden="true"></a>Error during authentication</h3><p>If the CLIENT_KEY_ID message contains the id outside of the expected range (which is a integer value beween 0 and 4), the server sends the SERVER_KEY_OUT_OF_RANGE_ERROR and closes the connection. For simplifaction of the implementation process the CLIENT_KEY_ID can contain even negative numbers (it doesn&#8217;t make sense in the context of this protocol). If the CLIENT_KEY_ID message contains something else than integer values (for example letters), the server sends SERVER_SYNTAX_ERROR message and closes the connection.</p>
<p>If the CLIENT_CONFIRMATION message contains the incorrect value (even the negative value), the server sends SERVER_LOGIN_FAILED message and closes the connection. If the CLIENT_CONFIRMATION contains anything else than numeric value, the server reacts with SERVER_SYNTAX_ERROR message and closes the connection.</p></section>
<section class="doc-section level-2"><h3 id="_syntax-error"><a class="anchor" href="#_syntax-error" aria-hidden="true"></a>Syntax error</h3><p>The server always reacts to the syntax error immediately after receiving the message in which it detected the error. The server sends the SERVER_SYNTAX_ERROR message to the robot and then terminates the connection as soon as possible. Syntactically incorrect messages:</p>
<div class="ulist"><ul><li>Imcomming message is longer than number of characters defined for each message (including the termination sequence \a\b). Message length is defined in client messages table.</li><li>Imcomming message syntax does not correspond to any of messages CLIENT_USERNAME, CLIENT_KEY_ID, CLIENT_CONFIRMATION, CLIENT_OK, CLIENT_RECHARGING and CLIENT_FULL_POWER.</li></ul></div>
<p>Each incommimg message is tested for the maximal size and only messages CLIENT_CONFIRMATION, CLIENT_OK, CLIENT_RECHARGING and CLIENT_FULL_POWER are tested for their content (messages CLIENT_USERNAME and CLIENT_MESSAGE can contain anything).</p></section>
<section class="doc-section level-2"><h3 id="_logic-error"><a class="anchor" href="#_logic-error" aria-hidden="true"></a>Logic error</h3><p>Logic error happens only during the recharging - when robot sends information about charging (CLIENT_RECHARGING) and then sends anything other than CLIENT_FULL_POWER or it sends CLIENT_FULL_POWER without sending CLIENT_RECHARGING before. Server reacts to these situations with SERVER_LOGIC_ERROR message and immediate termination of connection.</p></section>
<section class="doc-section level-2"><h3 id="_timeout"><a class="anchor" href="#_timeout" aria-hidden="true"></a>Timeout</h3><p>Protokol for communication with robots contains two timeout types:</p>
<div class="ulist"><ul><li>TIMEOUT - timeout for communication. If robot or server does not receive message from the other side for this time interval, they consider the connection to be lost and immediately terminate it.</li><li>TIMEOUT_RECHARGING - timeout for robot charging. After the server receives message CLIENT_RECHARGING, robot should at latest till this interval send message CLIENT_FULL_POWER. If robot does not manage it, server has to immediately terminate the connection.</li></ul></div></section></section>
<section class="doc-section level-1"><h2 id="_special-situations"><a class="anchor" href="#_special-situations" aria-hidden="true"></a>Special situations</h2><p>During the communication through some complicated network infrastructure two situations can take place:</p>
<div class="ulist"><ul><li>Message can arrive divided into several parts, which are read from the socket one at a time. (This happens due to segmentation and possible delay of some segments on the way through the network.)</li><li>Message, sent shortly after another one, may arrive almost simultaneously with it. They could be read together with one reading from the socket. (This happens, when the server does not manage to read the first message from the buffer before the second message arrives.)</li></ul></div>
<p>Using a direct connection between the server and the robots, combined with powerful hardware, these situations cannot occur naturally, so they are artificially created by the tester. In some tests, both situations are combined.</p>
<p>Every properly implemented server should be able to cope with this situation. Firmware of robots counts on this fact and even exploits it. If there are situations in the protocol where messages from the robot have a predetermined order, they are sent in that order at once. This allows robots to reduce their power consumption and simplifies protocol implementation (from their point of view).</p></section>
<section class="doc-section level-1"><h2 id="_server-optimization"><a class="anchor" href="#_server-optimization" aria-hidden="true"></a>Server optimization</h2><p>Server optimize the protokol so it does not wait for the end of the message, which is obviously bad. For example, only a part of the username message is sent for authentication. Server for example receives 22 characters of the username, but still does not receive the termination sequence \a\b. Since the maximum username message length is 20 characters, it is clear that the message received cannot be valid. Therefore, the server does not wait for the rest of the message, but sends a message SERVER_SYNTAX_ERROR and terminates the connection. In principle, server should react in the same way when receiving a secret message.</p>
<p>In the part of communication where robot is navigated to the target coordinates, server expects three possible messages: CLIENT_OK, CLIENT_RECHARGING, or CLIENT_FULL_POWER. If server reads a part of the incomplete message and this part is longer than the maximum length of these messages, it sends SERVER_SYNTAX_ERROR and terminates the connection. For the help with optimization, the maximum length for each message is listed in the table.</p></section>
<section class="doc-section level-1"><h2 id="_demo-communication"><a class="anchor" href="#_demo-communication" aria-hidden="true"></a>Demo communication</h2><div class="listing-block"><pre>C: "Oompa Loompa\a\b"
S: "107 KEY REQUEST\a\b"
C: "0\a\b"
S: "64907\a\b"
C: "8389\a\b"
S: "200 OK\a\b"
S: "102 MOVE\a\b"
C: "OK 0 0\a\b"
S: "102 MOVE\a\b"
C: "OK -1 0\a\b"
S: "104 TURN RIGHT\a\b"
C: "OK -1 0\a\b"
S: "104 TURN RIGHT\a\b"
C: "OK -1 0\a\b"
S: "102 MOVE\a\b"
C: "OK 0 0\a\b"
S: "105 GET MESSAGE\a\b"
C: "Secret message.\a\b"
S: "106 LOGOUT\a\b"</pre></div></section>
