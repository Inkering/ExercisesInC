#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

// read text file

// split file into words

// count frequency of each word and return

int update_hash(GHashTable *wordH, char *word) {
	int* hashVal = g_hash_table_lookup(wordH, word);

	// word not seen yet
	if (!hashVal) {
		int* cnt = malloc(sizeof(int));
		*cnt = 1;
		g_hash_table_insert(wordH, strdup(word), cnt);
		return *cnt;
	}
	(*hashVal)++;
	return *hashVal;
}

int main(int argc, char** argv) {
	// arguments will be for filename

	gsize len;
	// read file
	gchar *stringStuff, *fileTitle = argv[1];

	if (g_file_get_contents(fileTitle, &stringStuff, &len, NULL)) {
		// switches to the familiar JS regex parser (can use logical (OR |) to
		// set multiple option flags in this enum
		GRegexCompileFlags regexflags =
			(GRegexCompileFlags) (G_REGEX_JAVASCRIPT_COMPAT);

		// match spaces (\040) or newlines(\n), and some punctuation
		gchar *pattern = "\040|\n|;|,|[.]";
		gchar **matches = g_regex_split_simple(pattern, stringStuff, regexflags, 0);
		gchar *point = matches[0];

		// set hash type to be for strings (words) and based on equality.
		GHashTable *cnter = g_hash_table_new(g_str_hash, g_str_equal);

		int i = 0;
		while(point) {
			update_hash(cnter, point);
			i++;
			point = matches[i];
		}

		GList* keys = g_hash_table_get_keys(cnter);
		GList* values = g_hash_table_get_values(cnter);

		GList* key = keys;
		GList* value = values;
		while(TRUE) {
			if (key == NULL || value == NULL) {
				break;
			}
			printf("%d\t%s\n", *(int*) (value->data), (char*) (key->data));
			value = value->next;
			key = key->next;
		}
	}

	return 0;
}
