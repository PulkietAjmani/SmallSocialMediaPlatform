#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct User {
    int user_id;
    char name[50];
    char email[50];
    struct User* friends[100];
    int friend_count;
} User;

typedef struct Post {
    int post_id;
    User* user;
    char content[257];
    int likes;
    User* liked_by[100];
    int like_count;
} Post;

typedef struct Message {
    int message_id;
    User* sender;
    User* receiver;
    char content[257];
} Message;

// Define a temporary linked list node to store user names
typedef struct NameNode {
    char name[50];
    struct NameNode* next;
} NameNode;

// Function prototypes
User* create_user(const char* name, const char* email);
void add_friend(User* user1, User* user2);
void delete_friend(User* user1, User* user2);
void delete_user(User* user);
void print_users();
void change_user_name(User* user, char* new_name);
void change_user_email(User* user, char* new_email);
void print_friends(User* user);
User* search_user_by_name(const char* name);
User* search_user_by_email(const char* email);
User** mutual_friends(User* user1, User* user2);
void print_mutual_friends(User** friends);
Message* create_message(User* sender, User* receiver, const char* content);
void display_chat(User* user1, User* user2);
Post* new_post(User* user, const char* content);
void display_feed(User* user);
void testingParser(int arg1, char* arg2);
int is_friend(User* user1, User* user2);

#endif
