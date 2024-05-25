#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>
#include <sstream>
#include <string>
#include <thread>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "message.h"
#include "server.h"
#include "stl.h"
#include "user.h"

// TEST(MessageTests, DefaultConstructorValues) {
// 	// Testing default values of an empty message instance
// 	Message msg;
// 	EXPECT_EQ(msg.get_type(), "")
// 		<< "Expected default message type to be empty";
// 	EXPECT_EQ(msg.get_sender(), "") << "Expected default sender to be empty";
// 	EXPECT_EQ(msg.get_receiver(), "")
// 		<< "Expected default receiver to be empty";

// 	std::time_t now = std::time(0);
// 	std::string time = std::ctime(&now);
// 	time.erase(time.find_last_not_of(" \n\r\t") + 1);  // trim the string
// 	EXPECT_EQ(msg.get_time(), time)
// 		<< "Expected message time to match current time";
// }

// TEST(MessageTests, ParameterizedConstructorValues) {
// 	// Testing message initialization with specific values
// 	Message msg{"text", "david", "jenifer"};
// 	EXPECT_EQ(msg.get_type(), "text") << "Expected message type to be 'text'";
// 	EXPECT_EQ(msg.get_sender(), "david") << "Expected sender to be 'david'";
// 	EXPECT_EQ(msg.get_receiver(), "jenifer")
// 		<< "Expected receiver to be 'jenifer'";

// 	std::time_t now = std::time(0);
// 	std::string time = std::ctime(&now);
// 	time.erase(time.find_last_not_of(" \n\r\t") + 1);  // trim the string
// 	EXPECT_EQ(msg.get_time(), time)
// 		<< "Expected message time to match current time";
// }

// TEST(MessageTests, OutputStreamOverload) {
// 	// Testing the output stream operator for the Message class
// 	Message msg{"text", "david", "jenifer"};
// 	std::stringstream ss;
// 	ss << msg;
// 	size_t found_type = ss.str().find("text");
// 	size_t found_sender = ss.str().find("david");
// 	size_t found_receiver = ss.str().find("jenifer");
// 	EXPECT_TRUE(found_type != std::string::npos)
// 		<< "Message type not found in output stream";
// 	EXPECT_TRUE(found_sender != std::string::npos)
// 		<< "Sender not found in output stream";
// 	EXPECT_TRUE(found_receiver != std::string::npos)
// 		<< "Receiver not found in output stream";
// }

// TEST(MessageTests, TextMessageConstructorValues) {
// 	// Testing TextMessage initialization and attribute checks
// 	TextMessage textmsg("hello", "david", "jenifer");
// 	EXPECT_EQ(textmsg.get_text(), "hello")
// 		<< "Expected text message content to be 'hello'";
// 	EXPECT_EQ(textmsg.get_type(), "text")
// 		<< "Expected message type to be 'text'";
// 	EXPECT_EQ(textmsg.get_sender(), "david") << "Expected sender to be 'david'";
// 	EXPECT_EQ(textmsg.get_receiver(), "jenifer")
// 		<< "Expected receiver to be 'jenifer'";

// 	std::time_t now = std::time(0);
// 	std::string time = std::ctime(&now);
// 	time.erase(time.find_last_not_of(" \n\r\t") + 1);  // trim the string
// 	EXPECT_EQ(textmsg.get_time(), time)
// 		<< "Expected text message time to match current time";
// }

// TEST(MessageTests, TextMessageOutputStreamContent) {
// 	// Testing the output stream operator for the TextMessage class
// 	TextMessage textmsg("hello", "david", "jenifer");
// 	std::stringstream ss;
// 	ss << textmsg;
// 	size_t found = ss.str().find("hello");
// 	EXPECT_TRUE(found != std::string::npos)
// 		<< "Message text 'hello' not found in output stream";
// }

// TEST(MessageOutputTests, TextMessageDynamicPolymorphism) {
// 	// Testing dynamic polymorphism behavior by accessing derived class object
// 	// through base class pointer
// 	TextMessage textmsg("hello", "david", "jenifer");
// 	Message* msg = &textmsg;
// 	std::stringstream ss;
// 	ss << *msg;
// 	size_t found = ss.str().find("hello");
// 	EXPECT_TRUE(found != std::string::npos)
// 		<< "Text 'hello' not found in polymorphic output";
// }

// TEST(VoiceMessageTests, VoiceMessageAttributes) {
// 	// Testing attribute retrieval of a VoiceMessage object
// 	VoiceMessage voicemsg{"david", "jenifer"};
// 	EXPECT_EQ(voicemsg.get_voice().size(), 5)
// 		<< "Expected voice data size to be 5";
// 	EXPECT_EQ(voicemsg.get_type(), "voice")
// 		<< "Expected message type to be 'voice'";
// 	EXPECT_EQ(voicemsg.get_sender(), "david")
// 		<< "Expected sender to be 'david'";
// 	EXPECT_EQ(voicemsg.get_receiver(), "jenifer")
// 		<< "Expected receiver to be 'jenifer'";

// 	std::time_t now = std::time(0);
// 	std::string time = std::ctime(&now);
// 	time.erase(time.find_last_not_of(" \n\r\t") + 1);  // trim the string
// 	EXPECT_EQ(voicemsg.get_time(), time)
// 		<< "Expected voice message time to match current time";
// }

// TEST(VoiceMessageTests, VoiceMessageOutputStreamContent) {
// 	// Testing the output stream for the correct output of VoiceMessage content
// 	VoiceMessage voicemsg("david", "jenifer");
// 	std::stringstream ss;
// 	ss << voicemsg;
// 	int first_byte = static_cast<int>(voicemsg.get_voice()[0]);
// 	size_t found = ss.str().find(std::to_string(first_byte));
// 	EXPECT_TRUE(found != std::string::npos)
// 		<< "First byte of voice data not found in output stream";
// }

// TEST(VoiceMessageTests, VoiceMessageDynamicPolymorphism) {
// 	// Testing dynamic polymorphism with VoiceMessage to ensure proper info
// 	// output via base class pointer
// 	VoiceMessage voicemsg("david", "jenifer");
// 	Message* msg = &voicemsg;
// 	std::stringstream ss;
// 	ss << *msg;
// 	int first_byte = static_cast<int>(voicemsg.get_voice()[0]);
// 	size_t found = ss.str().find(std::to_string(first_byte));
// 	EXPECT_TRUE(found != std::string::npos)
// 		<< "First byte of voice data not found in polymorphic output";
// }

// TEST(UserTests, UserInitialization) {
// 	// Testing user initialization and attribute retrieval
// 	User user{"david", "", nullptr};
// 	EXPECT_EQ(user.get_username(), "david")
// 		<< "Expected username to be 'david'";
// }

// TEST(ServerTests, ServerInitialState) {
// 	// Testing initial state of server for users, public keys, and messages
// 	Server server;
// 	EXPECT_EQ(server.get_users().size(), 0) << "Expected no users initially";
// 	EXPECT_EQ(server.get_public_keys().size(), 0)
// 		<< "Expected no public keys initially";
// 	EXPECT_EQ(server.get_messages().size(), 0)
// 		<< "Expected no messages initially";
// }

// TEST(ServerUserManagementTests, CreateUserAndCheckInitialState) {
// 	// Test creation of a single user and check initial state of the server
// 	Server server;
// 	User david = server.create_user("david");

// 	EXPECT_EQ(david.get_username(), "david")
// 		<< "User 'david' should have the correct username";
// 	EXPECT_EQ(server.get_users().size(), 1)
// 		<< "Server should have exactly one user";
// 	EXPECT_EQ(server.get_public_keys().size(), 1)
// 		<< "Server should have exactly one public key";
// 	EXPECT_EQ(server.get_messages().size(), 0)
// 		<< "Server should have no messages initially";
// }

// TEST(ServerUserManagementTests, CreateUserThatAlreadyExists) {
// 	// Test attempting to create a user with a username that already exists
// 	Server server;
// 	User david = server.create_user("david");
// 	EXPECT_THROW(server.create_user("david"), std::logic_error)
// 		<< "Creating a user with an existing username should throw a "
// 		   "logic_error";
// }

// TEST(ServerMessagingTests, SendTextMessageBetweenUsers) {
// 	// Test sending a text message from one user to another
// 	Server server;
// 	User david = server.create_user("david");
// 	User jenifer = server.create_user("jenifer");

// 	bool result = david.send_text_message("hello jenifer", "jenifer");
// 	EXPECT_TRUE(result) << "Sending message should be successful";

// 	EXPECT_EQ(server.get_messages().size(), 1)
// 		<< "Server should have exactly one message";
// 	TextMessage* textmsg =
// 		reinterpret_cast<TextMessage*>(server.get_messages()[0]);
// 	EXPECT_EQ(textmsg->get_text(), "hello jenifer")
// 		<< "Message content should match sent text";
// }

// TEST(ServerMessagingTests, SendVoiceMessageBetweenUsers) {
// 	// Test sending a voice message from one user to another
// 	Server server;
// 	User david = server.create_user("david");
// 	User jenifer = server.create_user("jenifer");

// 	bool result = david.send_voice_message("jenifer");
// 	EXPECT_TRUE(result) << "Sending voice message should be successful";

// 	EXPECT_EQ(server.get_messages().size(), 1)
// 		<< "Server should have exactly one voice message";
// 	VoiceMessage* voicemsg =
// 		reinterpret_cast<VoiceMessage*>(server.get_messages()[0]);
// 	EXPECT_EQ(voicemsg->get_voice().size(), 5)
// 		<< "Voice message size should be 5";
// }

// TEST(ServerMessagingTests, SendMessageToNonexistentUser) {
// 	// Test sending a message to a user that does not exist
// 	Server server;
// 	User david = server.create_user("david");

// 	bool result = david.send_text_message("hello jenifer", "jenifer");
// 	EXPECT_FALSE(result) << "Sending message to a nonexistent user should fail";
// 	EXPECT_EQ(server.get_messages().size(), 0)
// 		<< "No messages should be stored in the server";
// }

// TEST(ServerMessageCreationTests, CreateMessageWithIncorrectSignature) {
// 	// Test message creation with an incorrect digital signature
// 	Server server;
// 	User david = server.create_user("david");
// 	User jenifer = server.create_user("jenifer");

// 	VoiceMessage* voicemsg = new VoiceMessage("david", "jenifer");
// 	bool result = server.create_message(voicemsg, "wrong signature");
// 	EXPECT_FALSE(result)
// 		<< "Message creation with incorrect signature should fail";
// 	EXPECT_EQ(server.get_messages().size(), 0)
// 		<< "No messages should be stored in the server";
// }

// TEST(ServerMessagingTests, SendMultipleMessagesAndVoiceMessage) {
// 	// Test sending multiple text messages and a voice message across different
// 	// users
// 	Server server;
// 	User david = server.create_user("david");
// 	User jenifer = server.create_user("jenifer");
// 	User john = server.create_user("john");

// 	david.send_text_message("hello jenifer", "jenifer");
// 	jenifer.send_text_message("hi there", "david");
// 	john.send_text_message("how you do'in", "david");
// 	jenifer.send_voice_message("david");

// 	EXPECT_EQ(server.get_messages().size(), 4)
// 		<< "Server should have exactly four messages";
// }

// TEST(ServerMessagingAnalysisTests, GetMessagesFromUser) {
// 	// Test retrieving messages sent by a specific user
// 	Server server;
// 	User david = server.create_user("david");
// 	User jenifer = server.create_user("jenifer");
// 	User john = server.create_user("john");

// 	david.send_text_message("hello jenifer", "jenifer");
// 	jenifer.send_text_message("hi there", "david");
// 	john.send_text_message("how you do'in", "david");
// 	jenifer.send_voice_message("david");
// 	david.send_voice_message("john");
// 	david.send_voice_message("jenifer");

// 	auto msgs = server.get_all_messages_from("david");
// 	EXPECT_EQ(msgs.size(), 3) << "Expected three messages sent by david";
// 	EXPECT_EQ(msgs[1]->get_type(), "voice")
// 		<< "Second message should be a voice message";
// }

// TEST(ServerMessagingAnalysisTests, GetMessagesToUser) {
// 	// Test retrieving messages sent to a specific user
// 	Server server;
// 	User david = server.create_user("david");
// 	User jenifer = server.create_user("jenifer");
// 	User john = server.create_user("john");

// 	david.send_text_message("hello jenifer", "jenifer");
// 	jenifer.send_text_message("hi there", "david");
// 	john.send_text_message("how you do'in", "david");
// 	jenifer.send_voice_message("david");
// 	david.send_voice_message("john");
// 	david.send_voice_message("jenifer");

// 	auto msgs = server.get_all_messages_to("jenifer");
// 	EXPECT_EQ(msgs.size(), 2) << "Expected two messages addressed to jenifer";
// 	EXPECT_EQ(msgs[0]->get_type(), "text")
// 		<< "First message should be a text message";
// }

// TEST(ServerMessagingAnalysisTests, GetChatBetweenUsers) {
// 	// Test retrieving chat messages between two specific users
// 	Server server;
// 	User david = server.create_user("david");
// 	User jenifer = server.create_user("jenifer");
// 	User john = server.create_user("john");

// 	david.send_text_message("hello jenifer", "jenifer");
// 	jenifer.send_text_message("hi there", "david");
// 	john.send_text_message("how you do'in", "david");
// 	jenifer.send_voice_message("david");
// 	david.send_voice_message("john");
// 	david.send_voice_message("jenifer");

// 	auto msgs = server.get_chat("david", "jenifer");
// 	EXPECT_EQ(msgs.size(), 4)
// 		<< "Expected four messages in chat between david and jenifer";
// 	TextMessage* msg1 = reinterpret_cast<TextMessage*>(msgs[1]);
// 	EXPECT_EQ(msg1->get_text(), "hi there")
// 		<< "Second message in chat should be 'hi there' from jenifer";
// }

// TEST(MessageSortingTests, SortMessagesByTimestamp) {
// 	// Test sorting messages by timestamp
// 	std::vector<Message*> msgs;
// 	msgs.push_back(new TextMessage("message 1", "david", "jenifer"));
// 	std::this_thread::sleep_for(std::chrono::seconds(1));
// 	msgs.push_back(new TextMessage("message 2", "jenifer", "david"));
// 	std::this_thread::sleep_for(std::chrono::seconds(1));
// 	msgs.push_back(new TextMessage("message 3", "david", "jenifer"));
// 	std::this_thread::sleep_for(std::chrono::seconds(1));
// 	msgs.push_back(new TextMessage("message 4", "jenifer", "david"));

// 	auto rng = std::default_random_engine{};
// 	std::shuffle(std::begin(msgs), std::end(msgs), rng);

// 	Server::sort_msgs(msgs);
// 	EXPECT_EQ(reinterpret_cast<TextMessage*>(msgs[0])->get_text(), "message 1")
// 		<< "First message should be 'message 1'";
// 	EXPECT_EQ(reinterpret_cast<TextMessage*>(msgs[1])->get_text(), "message 2")
// 		<< "Second message should be 'message 2'";
// 	EXPECT_EQ(reinterpret_cast<TextMessage*>(msgs[2])->get_text(), "message 3")
// 		<< "Third message should be 'message 3'";
// 	EXPECT_EQ(reinterpret_cast<TextMessage*>(msgs[3])->get_text(), "message 4")
// 		<< "Fourth message should be 'message 4'";
// }

// TEST(VectorInitializationTests, InitializeAndMultiplyVector) {
// 	// Test vector initialization and element multiplication
// 	std::vector<int> v;
// 	initial_vector_with_3_mutiplies(v, 3);
// 	EXPECT_TRUE((v == std::vector<int>{3, 6, 9}))
// 		<< "Vector should contain multiples of 3";

// 	initial_vector_with_3_mutiplies(v, 4);
// 	EXPECT_TRUE((v == std::vector<int>{3, 6, 9, 12}))
// 		<< "Vector should now contain 12 as a multiple of 4";

// 	initial_vector_with_3_mutiplies(v, 6);
// 	EXPECT_TRUE((v == std::vector<int>{3, 6, 9, 12, 15, 18}))
// 		<< "Vector should now contain multiples of 6";
// }

// TEST(VectorAnalysisTests, CountUniqueElementsAboveThreshold) {
// 	// Test counting unique elements in a vector above a certain threshold
// 	std::vector<int> v1{1, 2, 3, 1, 2, 3, 1, 2, 5, 5, 6, 5, 7, 8, 4,
// 						5, 6, 7, 1, 2, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4};
// 	EXPECT_EQ(count_unique_above(v1, 5), 4)
// 		<< "There should be 4 unique elements above 5";

// 	std::vector<int> v2{1,	2,	3,	4,	5,	6,	1,	2,	34, 6,	8,
// 						4,	5,	7,	8,	3,	5,	6,	7,	8,	11, 32,
// 						55, 11, 32, 44, 55, 54, 29, 44, 6,	44, 99};
// 	EXPECT_EQ(count_unique_above(v2, 30), 6)
// 		<< "There should be 6 unique elements above 30";
// }

// TEST(VectorManipulationTests, ReverseAndConcatenateVectorElements) {
// 	// Test reversing a vector and concatenating its elements into a string with
// 	// a delimiter
// 	std::vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8, 9};
// 	EXPECT_EQ(vector_to_string(v1, ','), "9,8,7,6,5,4,3,2,1")
// 		<< "Vector elements should be reversed and concatenated with ','";

// 	std::vector<int> v2{1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 14};
// 	EXPECT_EQ(vector_to_string(v2, '*'), "14*12*9*8*7*6*5*4*3*2*1")
// 		<< "Vector elements should be reversed and concatenated with '*'";
// }

// // Test suite for square_elements
// TEST(SquareElementsTest, HandlesEmptyVector) {
// 	std::vector<int> v{};
// 	square_elements(v);
// 	EXPECT_TRUE(v.empty());
// }

// TEST(SquareElementsTest, HandlesVectorWithPositiveNumbers) {
// 	std::vector<int> v{1, 2, 3, 4};
// 	square_elements(v);
// 	EXPECT_EQ(v, std::vector<int>{1, 4, 9, 16});
// }

// TEST(SquareElementsTest, HandlesVectorWithNegativeNumbers) {
// 	std::vector<int> v{-1, -2, -3, -4};
// 	square_elements(v);
// 	EXPECT_EQ(v, std::vector<int>{1, 4, 9, 16});
// }

// TEST(SquareElementsTest, HandlesVectorWithMixedNumbers) {
// 	std::vector<int> v{-1, 2, -3, 4};
// 	square_elements(v);
// 	EXPECT_EQ(v, std::vector<int>{1, 4, 9, 16});
// }

// TEST(SquareElementsTest, HandlesVectorWithZeros) {
// 	std::vector<int> v{0, 0, 0, 0};
// 	square_elements(v);
// 	EXPECT_EQ(v, std::vector<int>{0, 0, 0, 0});
// }

// TEST(SquareElementsTest, HandlesLargeNumbers) {
// 	std::vector<int> v{1000, -1000};
// 	square_elements(v);
// 	EXPECT_EQ(v, std::vector<int>{1000000, 1000000});
// }

// TEST(SquareElementsTest, NoOverflowCheck) {
// 	std::vector<int> v{100000, -100000};
// 	square_elements(v);
// 	// Check if the function correctly squares large numbers, ignoring integer
// 	// overflow scenarios
// 	EXPECT_EQ(v,
// 			  std::vector<int>{10000000000,
// 							   10000000000});  // This test might fail on some
// 											   // systems due to overflow
// }

// // Test suite for copy_if_even
// TEST(CopyIfEvenTest, HandlesEmptySource) {
// 	std::vector<int> source{};
// 	std::vector<int> destination{
// 		1, 2, 3};  // Intentionally pre-filled to test clearing
// 	copy_if_even(source, destination);
// 	EXPECT_TRUE(destination.empty());
// }

// TEST(CopyIfEvenTest, HandlesSourceWithOnlyEvenNumbers) {
// 	std::vector<int> source{2, 4, 6, 8};
// 	std::vector<int> destination;
// 	copy_if_even(source, destination);
// 	EXPECT_EQ(destination, source);
// }

// TEST(CopyIfEvenTest, HandlesSourceWithOnlyOddNumbers) {
// 	std::vector<int> source{1, 3, 5, 7};
// 	std::vector<int> destination;
// 	copy_if_even(source, destination);
// 	EXPECT_TRUE(destination.empty());
// }

// TEST(CopyIfEvenTest, HandlesSourceWithMixedNumbers) {
// 	std::vector<int> source{1, 2, 3, 4};
// 	std::vector<int> destination;
// 	copy_if_even(source, destination);
// 	EXPECT_EQ(destination, std::vector<int>{2, 4});
// }

// TEST(CopyIfEvenTest, HandlesLargeNumbers) {
// 	std::vector<int> source{100000, 100001};
// 	std::vector<int> destination;
// 	copy_if_even(source, destination);
// 	EXPECT_EQ(destination, std::vector<int>{100000});
// }
