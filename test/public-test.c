#define MAX_WORD_SIZE 46

#define _POSIX_C_SOURCE 1

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
// Include the check header file:
#include <check.h>

// Include assignment header file:
#include "../hw.h"


void setup() {
	// Perform any setup operations.
}

void teardown() {
	// Perform any teardown operations.
}

// Example test.
//  For more details see http://check.sourceforge.net
START_TEST(test_words_next_word) // points=5
{
	int p[2];
	// Create a pipe:
	pipe(p);

	// Close normal stdout:
	close(1);
	// Make stdout same as p[1]:
	dup(p[1]);

	// Close normal stdin:
	close(0);
	// Make stdin same as p[0]:
	dup(p[0]);

	// Write a string to "stdout"
	printf("this,,,$$$is     some text!!EXCELLENT\n");
	char buf[MAX_WORD_SIZE];
        char  *word = buf;
	//int nbytes;

	// Test word 1:
	word = words_next_word();
	ck_assert_msg(word != NULL, "words_next_word() is returning NULL!");
	ck_assert_str_eq("this", word);
	ck_assert_int_eq(strlen(word), 4);
	// Test word 2:
	word = words_next_word();
	ck_assert_msg(word != NULL, "words_next_word() is returning NULL!");
	ck_assert_str_eq("is", word);
	ck_assert_int_eq(strlen(word), 2);
	// Test word 3:
	word = words_next_word();
	ck_assert_msg(word != NULL, "words_next_word() is returning NULL!");
	ck_assert_str_eq("some", word);
	ck_assert_int_eq(strlen(word), 4);
	// Test word 4:
	word = words_next_word();
	ck_assert_msg(word != NULL, "words_next_word() is returning NULL!");
	ck_assert_str_eq("text", word);
	ck_assert_int_eq(strlen(word), 4);
	// Test word 5:
	word = words_next_word();
	ck_assert_msg(word != NULL, "words_next_word() is returning NULL!");
	ck_assert_str_eq("EXCELLENT", word);
	ck_assert_int_eq(strlen(word), 9);
}
END_TEST

// An example of a test that fails - so you can see the output!
START_TEST(test_wset_new)
{
	WordSet* wset = wset_new();
	ck_assert_msg(wset != NULL, "The wset_new function is returning NULL!");
}
END_TEST

START_TEST(test_wset_free)
{
	WordSet* wset = wset_new();
	ck_assert_msg(wset != NULL, "The wset_new function is returning NULL!");
	wset_free(wset);
}
END_TEST

START_TEST(test_wset_add)
{
	WordSet* wset = wset_new();
	ck_assert_msg(wset != NULL, "The wset_new function is returning NULL!");
	wset_add(wset, "this");
	ck_assert_int_eq(wset_size(wset), 1);
	wset_add(wset, "is");
	ck_assert_int_eq(wset_size(wset), 2);
	wset_add(wset, "some");
	ck_assert_int_eq(wset_size(wset), 3);
	wset_add(wset, "text");
	ck_assert_int_eq(wset_size(wset), 4);
}
END_TEST

START_TEST(test_wset_fast_add)
{
	WordSet* wset = wset_new();
	ck_assert_msg(wset != NULL, "The wset_new function is returning NULL!");
	wset_fast_add(wset, "this");
	ck_assert_int_eq(wset_size(wset), 1);
	wset_fast_add(wset, "is");
	ck_assert_int_eq(wset_size(wset), 2);
	wset_fast_add(wset, "some");
	ck_assert_int_eq(wset_size(wset), 3);
	wset_fast_add(wset, "text");
	ck_assert_int_eq(wset_size(wset), 4);
}
END_TEST

START_TEST(test_wset_exists)
{
	WordSet* wset1 = wset_new();
	ck_assert_msg(wset1 != NULL, "The wset_new function is returning NULL!");
	wset_add(wset1, "this");
	wset_add(wset1, "is");
	wset_add(wset1, "some");
	wset_add(wset1, "text");
	ck_assert_int_eq(wset_exists(wset1, "this"), 1);
	ck_assert_int_eq(wset_exists(wset1, "is"), 1);
	ck_assert_int_eq(wset_exists(wset1, "some"), 1);
	ck_assert_int_eq(wset_exists(wset1, "text"), 1);

	WordSet* wset2 = wset_new();
	ck_assert_msg(wset2 != NULL, "The wset_new function is returning NULL!");
	wset_fast_add(wset2, "this");
	wset_fast_add(wset2, "is");
	wset_fast_add(wset2, "some");
	wset_fast_add(wset2, "text");
	ck_assert_int_eq(wset_exists(wset2, "this"), 1);
	ck_assert_int_eq(wset_exists(wset2, "is"), 1);
	ck_assert_int_eq(wset_exists(wset2, "some"), 1);
	ck_assert_int_eq(wset_exists(wset2, "text"), 1);
}
END_TEST

START_TEST(test_wset_remove)
{
	WordSet* wset2 = wset_new();
	ck_assert_msg(wset2 != NULL, "The wset_new function is returning NULL!");
	wset_fast_add(wset2, "this");
	wset_fast_add(wset2, "is");
	wset_fast_add(wset2, "some");
	wset_fast_add(wset2, "text");
	ck_assert_int_eq(wset_size(wset2), 4);

	wset_remove(wset2, "this");
	wset_remove(wset2, "text");
	ck_assert_int_eq(wset_size(wset2), 2);

	wset_remove(wset2, "is");
	wset_remove(wset2, "some");
	ck_assert_int_eq(wset_size(wset2), 0);
}
END_TEST

START_TEST(test_wset_freq)
{
	WordSet* wset2 = wset_new();
	ck_assert_msg(wset2 != NULL, "The wset_new function is returning NULL!");
	wset_fast_add(wset2, "this");
	wset_fast_add(wset2, "this");
	wset_fast_add(wset2, "this");
	wset_fast_add(wset2, "this");
	ck_assert_int_eq(wset_freq(wset2, "this"), 4);
}
END_TEST

// Example test.
//  For more details see http://check.sourceforge.net
START_TEST(test_words_next_word2) // points=5
{
	int p[2];
	FILE *fp;
	fp = fopen("sample.txt", "w");
	//fp = fopen("test.txt","r");
	// Create a pipe:
	pipe(p);
    
	// Make stdout same as p[1]:
	dup2(p[1], fileno(fp));
    
	// Close normal stdin:
	close(0);
	// Make stdin same as p[0]:
	dup(p[0]);
    
	// Write a string to file fp
	fprintf(fp,"&&&this,,,$$$is     some tExt12!!EXCELLENT## ");
	fflush(fp);
	fclose(fp);
	close(p[1]);
	char buf[MAX_WORD_SIZE];
    	char  *word = buf;
	//int nbytes;
    
	// Test word 1:
	word = words_next_word();
	ck_assert_msg(word != NULL, "words_next_word() is returning NULL!");
	ck_assert_str_eq("this", word);
	ck_assert_int_eq(strlen(word), 4);
	// Test word 2:
	word = words_next_word();
	ck_assert_msg(word != NULL, "words_next_word() is returning NULL!");
	ck_assert_str_eq("is", word);
	ck_assert_int_eq(strlen(word), 2);
	// Test word 3:
	word = words_next_word();
	ck_assert_msg(word != NULL, "words_next_word() is returning NULL!");
	ck_assert_str_eq("some", word);
	ck_assert_int_eq(strlen(word), 4);
	// Test word 4:
	word = words_next_word();
	ck_assert_msg(word != NULL, "words_next_word() is returning NULL!");
	ck_assert_str_eq("tExt12", word);
	ck_assert_int_eq(strlen(word), 6);
	// Test word 5:
	word = words_next_word();
	ck_assert_msg(word != NULL, "words_next_word() is returning NULL!");
	ck_assert_str_eq("EXCELLENT", word);
	ck_assert_int_eq(strlen(word), 9);
	// After all legal words have been read, words_next_word should return NULL
	word = words_next_word();
	ck_assert_msg(word == NULL, "words_next_word() should be NULL after EOF");
	//fclose(fp);	

}
END_TEST

START_TEST(test_wset_add2)
{
// Return value: 
// Frequency of word added into the set.
//
// Implementation details:
// There are two possible implementations of wset_add, one that adds elements to
// the end of the list and one that adds elements to the beginning of the list.
// These tests don't check for any specific scheme but makes sure that the 
// frequency is returned and the size of the set is incremented.

	WordSet* wset = wset_new();
	ck_assert_msg(wset != NULL, "The wset_new function is returning NULL!");
	ck_assert_int_eq(wset_add(wset, "this"), 1);  	// checks if the frequency of the word added is correct
	ck_assert_int_eq(wset_size(wset), 1); 		// checks if the size of the set is correct

	ck_assert_int_eq(wset_add(wset, "is"), 1);
	ck_assert_int_eq(wset_size(wset), 2);

	ck_assert_int_eq(wset_add(wset, "some"), 1);
	ck_assert_int_eq(wset_size(wset), 3);
	
	ck_assert_int_eq(wset_add(wset, "text"), 1);
	ck_assert_int_eq(wset_size(wset), 4);

// Adding existing words --> size shouldn't increase
	ck_assert_int_eq(wset_add(wset, "this"), 2);
	ck_assert_int_eq(wset_size(wset),4);

	ck_assert_int_eq(wset_add(wset, "text"), 2);
	ck_assert_int_eq(wset_size(wset),4);
	
}
END_TEST

START_TEST(test_wset_fast_add2)
{
// Return value: 
// Frequency of word added into the set.
//
// Implementation details:
// The write seems to indicate that only existing words if accessed again need to be 
// moved to the head of the list. But the implicit understanding would be that existing
// words AND newly inserted words should be moved to the head of the list. The tests
// below assume the latter.
//
// Edge cases:
// If the word which is the head of the list is accessed again, then the students' 
// implementation shouldn't introduce infinite loops or cause seg faults. Both of them
// occur when the previous pointers are incorrectly used.

	WordSet* wset = wset_new();
	ck_assert_msg(wset != NULL, "The wset_new function is returning NULL!");

// New words become head
	ck_assert_int_eq(wset_fast_add(wset, "this"), 1);	// checks if the frequency of the word added is correct
	ck_assert_int_eq(wset_size(wset), 1);			// checks of the size of the set is correct
	ck_assert_str_eq(wset_head_word(wset), "this");		// checks if the word added is made the head of the set

	ck_assert_int_eq(wset_fast_add(wset, "is"), 1);
	ck_assert_int_eq(wset_size(wset), 2);
	ck_assert_str_eq(wset_head_word(wset), "is");
	
	ck_assert_int_eq(wset_fast_add(wset, "some"), 1);
	ck_assert_int_eq(wset_size(wset), 3);
	ck_assert_str_eq(wset_head_word(wset), "some");
	
	ck_assert_int_eq(wset_fast_add(wset, "text"), 1);
	ck_assert_int_eq(wset_size(wset), 4);
	ck_assert_str_eq(wset_head_word(wset), "text");

// Existing words become head
	ck_assert_int_eq(wset_fast_add(wset, "text"), 2);
	ck_assert_int_eq(wset_size(wset), 4);
	ck_assert_str_eq(wset_head_word(wset), "text");
	
	ck_assert_int_eq(wset_fast_add(wset, "some"), 2);
	ck_assert_int_eq(wset_size(wset), 4);
	ck_assert_str_eq(wset_head_word(wset), "some");
}
END_TEST

START_TEST(test_wset_exists2)
{
// Return value:
// 1 if the word exists and 0 if it doesn't.

	WordSet* wset1 = wset_new();
	ck_assert_msg(wset1 != NULL, "The wset_new function is returning NULL!");
	wset_add(wset1, "this");
	wset_add(wset1, "is");
	wset_add(wset1, "some");
	wset_add(wset1, "text");
	wset_add(wset1, "this");
	wset_add(wset1, "text");
	ck_assert_int_eq(wset_exists(wset1, "this"), 1);
	ck_assert_int_eq(wset_exists(wset1, "is"), 1);
	ck_assert_int_eq(wset_exists(wset1, "some"), 1);
	ck_assert_int_eq(wset_exists(wset1, "text"), 1);
	ck_assert_int_eq(wset_exists(wset1, "that"), 0);
    
	WordSet* wset2 = wset_new();
	ck_assert_msg(wset2 != NULL, "The wset_new function is returning NULL!");
	wset_fast_add(wset2, "this");
	wset_fast_add(wset2, "is");
	wset_fast_add(wset2, "some");
	wset_fast_add(wset2, "text");
	wset_fast_add(wset2, "text");
	wset_fast_add(wset2, "this");
	ck_assert_int_eq(wset_exists(wset2, "this"), 1);
	ck_assert_int_eq(wset_exists(wset2, "is"), 1);
	ck_assert_int_eq(wset_exists(wset2, "some"), 1);
	ck_assert_int_eq(wset_exists(wset2, "text"), 1);
	ck_assert_int_eq(wset_exists(wset2, "that"), 0);
}
END_TEST

START_TEST(test_wset_remove2)
{
// Return value:
// Frequency of the removed word if it existed in the set or -1.
//
// Implementation detail:
// We test wset_remove using wset_fast_add and not add because of the different ways 
// to implement wset_add.
//
// Edge cases:
// When the head node is removed, new head should be reassigned correctly. Incorrect 
// implementations may not reassign a new head.
// When the tail is removed, the previous node should point to NULL to indicate the new
// last node.

	WordSet* wset2 = wset_new();
	ck_assert_msg(wset2 != NULL, "The wset_new function is returning NULL!");
	wset_fast_add(wset2, "this");
	
	ck_assert_int_eq(wset_remove(wset2, "that"), -1);
	
	wset_fast_add(wset2, "is");
	wset_fast_add(wset2, "some");
	wset_fast_add(wset2, "text");
	ck_assert_int_eq(wset_size(wset2), 4);

	// Removing non-existing word
	ck_assert_int_eq(wset_remove(wset2, "that"), -1);

	// Removing an intermediate node in the set
	wset_remove(wset2,"is");
	ck_assert_int_eq(wset_size(wset2), 3);

	// Making "text" the head
	wset_fast_add(wset2, "text");
	ck_assert_str_eq(wset_head_word(wset2), "text");

	// Making "some" the head. The order of words should be "some"->"text"->"this"->NULL
	wset_fast_add(wset2, "some");
	ck_assert_str_eq(wset_head_word(wset2), "some");

	// Remove the head node
	ck_assert_int_eq(wset_freq(wset2, "some"), wset_remove(wset2, "some"));
	ck_assert_int_eq(wset_size(wset2), 2);

	ck_assert_str_eq(wset_head_word(wset2), "text");

	// Remove the tail node
	ck_assert_int_eq(wset_freq(wset2, "this"), wset_remove(wset2, "this"));
	ck_assert_int_eq(wset_size(wset2), 1);
	
	ck_assert_str_eq(wset_head_word(wset2), "text");

	ck_assert_int_eq(wset_remove(wset2, "that"), -1);

	wset_remove(wset2,"text");
	ck_assert_int_eq(wset_size(wset2), 0);

}
END_TEST

START_TEST(test_wset_freq2)
{
// Return value:
// Frequency of the word if it exists or 0 if it doesn't exist

	WordSet* wset1 = wset_new();
	ck_assert_msg(wset1 != NULL, "The wset_new function is returning NULL!");
	wset_add(wset1, "this");
	wset_add(wset1, "is");
	wset_add(wset1, "some");
	wset_add(wset1, "text");
	wset_add(wset1, "this");
	ck_assert_int_eq(wset_freq(wset1, "this"), 2);
	ck_assert_int_eq(wset_freq(wset1, "that"), 0);
	
	WordSet* wset2 = wset_new();
	ck_assert_msg(wset2 != NULL, "The wset_new function is returning NULL!");
	wset_fast_add(wset2, "this");
	wset_fast_add(wset2, "is");
	wset_fast_add(wset2, "some");
	wset_fast_add(wset2, "text");
	wset_fast_add(wset2, "this");
	ck_assert_int_eq(wset_freq(wset2, "this"), 2);
	ck_assert_int_eq(wset_freq(wset2, "that"), 0);
}
END_TEST


Suite* tester_suite() {
	// Create the test suite:
	Suite* s = suite_create("Public Assignment Tests");

	/**** BEGIN UNIT TESTS ****/
	TCase* tc_inc = tcase_create("Public Tests");
	// To use setup/teardown (otherwise skip):
	tcase_add_checked_fixture(tc_inc, setup, teardown);
	tcase_add_test(tc_inc, test_words_next_word);
	tcase_add_test(tc_inc, test_wset_new);
	tcase_add_test(tc_inc, test_wset_free);
	tcase_add_test(tc_inc, test_wset_add);
	tcase_add_test(tc_inc, test_wset_fast_add);
	tcase_add_test(tc_inc, test_wset_remove);
	tcase_add_test(tc_inc, test_wset_exists);
	tcase_add_test(tc_inc, test_wset_freq);
	tcase_add_test(tc_inc, test_words_next_word2);
	tcase_add_test(tc_inc, test_wset_add2);
	tcase_add_test(tc_inc, test_wset_fast_add2);
	tcase_add_test(tc_inc, test_wset_remove2);
	tcase_add_test(tc_inc, test_wset_exists2);
	tcase_add_test(tc_inc, test_wset_freq2);
	// Add unit tests to test suite:
	suite_add_tcase(s, tc_inc);
	/**** END UNIT TESTS   ****/

	// Return the suite:
	return s;
}

int main(int argc, char* argv[]) {
	int number_failed;
	Suite* s = tester_suite();
	SRunner* sr = srunner_create(s);
	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);

	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
