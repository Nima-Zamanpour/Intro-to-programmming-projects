typedef struct good {
	char* good_name;
	char* seller_name;
	long int price;
	int count;
	float rate;
	int rated;      //used for buyers to vote only once
	//also used to check whether good belongs to a seller or a buyer
	int numofrate;  //only for sellers
	struct good* right, * left;
}good;
typedef struct person {
	char* username;
	char* password;
	char* role;
	long int wallet;
	int log_status;
	good* goods;                          //for different kinds of goods.
	struct person* right, * left;
}person;
void view_show_search(char* entery,struct person* Person);
void deposit_buy_rate(char* entery, struct person* root);
void add_remove_change(char* entery,struct person* root);
int alphabet_check(char* temp1, char* temp_next);
person* signup(char* entery, struct person* root);
void log(char* entery, struct person* Person);
person* insert(person* Person, person* tree);
good* good_insert(good* Good, good* tree);
person* log_check(person* root);
void File_writer(person* root);
char* Entery(char* entery);
void freeGood(good* Good);
person* File_reader();
