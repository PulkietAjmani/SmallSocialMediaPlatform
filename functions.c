#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 10000
#define MAX_MESSAGES 50
#define MAX_FEED 20

// Global variables
static User* all_users[MAX_USERS];
static int user_count = 0;
static int user_id_counter = 0;

static Post* all_posts[MAX_USERS * 10];
static int post_count = 0;
static int post_id_counter = 0;

static Message* all_messages[MAX_USERS * 10];
static int message_count = 0;
static int message_id_counter = 0;



// Utility Functions
int is_friend(User* user1, User* user2) {
    if (!user1 || !user2) return 0;
    for (int i = 0; i < user1->friend_count; i++) {
        if (user1->friends[i] == user2) {
            return 1;
        }
    }
    return 0;
}

void sort_users(User** users, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(users[i]->name, users[j]->name) > 0) {
                User* temp = users[i];
                users[i] = users[j];
                users[j] = temp;
            }
        }
    }
}

// Function Implementations
void testingParser(int arg1, char *arg2) {
    printf("The parser was called with arguments: %d and %s\n", arg1, arg2);
}

User* create_user(const char* name, const char* email) {
    if (user_count >= MAX_USERS) {
        printf("Error: Maximum user limit reached.\n");
        return NULL;
    }
    User* new_user = (User*)malloc(sizeof(User));
    new_user->user_id = user_id_counter++;
    strcpy(new_user->name, name);
    strcpy(new_user->email, email);
    new_user->friend_count = 0;
    all_users[user_count++] = new_user;
    return new_user;
}

void add_friend(User* user1, User* user2) {
    if (!user1 || !user2 || is_friend(user1, user2)) return;
    user1->friends[user1->friend_count++] = user2;
    user2->friends[user2->friend_count++] = user1;
}

void delete_friend(User* user1, User* user2) {
    if (!user1 || !user2) return;
    for (int i = 0; i < user1->friend_count; i++) {
        if (user1->friends[i] == user2) {
            user1->friends[i] = user1->friends[--user1->friend_count];
            break;
        }
    }
    for (int i = 0; i < user2->friend_count; i++) {
        if (user2->friends[i] == user1) {
            user2->friends[i] = user2->friends[--user2->friend_count];
            break;
        }
    }
}

void delete_user(User* user) {
    if (!user) return;
    for (int i = 0; i < user->friend_count; i++) {
        delete_friend(user, user->friends[i]);
    }
    for (int i = 0; i < user_count; i++) {
        if (all_users[i] == user) {
            all_users[i] = all_users[--user_count];
            break;
        }
    }
    free(user);
}




void print_friends(User* user) {
    if (!user) {
        printf("Error: User not found.\n");
        return;
    }

    if (user->friend_count == 0) {
        printf("\n");
        return;
    }

    // Sort friends alphabetically
    sort_users(user->friends, user->friend_count);

    // Print friends as comma-separated list
    for (int i = 0; i < user->friend_count; i++) {
        printf("%s", user->friends[i]->name);
        if (i < user->friend_count - 1) printf(","); // No extra space here
    }
    printf("\n");
}




User* search_user_by_name(const char* name) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(all_users[i]->name, name) == 0) {
            return all_users[i];
        }
    }
    return NULL;
}

User* search_user_by_email(const char* email) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(all_users[i]->email, email) == 0) {
            return all_users[i];
        }
    }
    return NULL;
}

void change_user_name(User* user, char* new_name) {
    if (user) strcpy(user->name, new_name);
}

void change_user_email(User* user, char* new_email) {
    if (user) strcpy(user->email, new_email);
}

User** mutual_friends(User* user1, User* user2) {
    static User* mutuals[MAX_USERS];
    int count = 0;
    for (int i = 0; i < user1->friend_count; i++) {
        for (int j = 0; j < user2->friend_count; j++) {
            if (user1->friends[i] == user2->friends[j]) {
                mutuals[count++] = user1->friends[i];
            }
        }
    }
    mutuals[count] = NULL;
    return mutuals;
}

void print_mutual_friends(User** friends) {
    if (!friends) return;
    for (int i = 0; friends[i]; i++) {
        printf("%s", friends[i]->name);
        if (friends[i + 1]) printf(",");
    }
    printf("\n");
}

Message* create_message(User* sender, User* receiver, const char* content) {
    if (!sender || !receiver) return NULL;
    Message* message = (Message*)malloc(sizeof(Message));
    message->message_id = message_id_counter++;
    message->sender = sender;
    message->receiver = receiver;
    strcpy(message->content, content);
    all_messages[message_count++] = message;
    return message;
}

void display_chat(User* user1, User* user2) {
    for (int i = 0; i < message_count; i++) {
        Message* message = all_messages[i];
        if ((message->sender == user1 && message->receiver == user2) || 
            (message->sender == user2 && message->receiver == user1)) {
            printf("[%s:] %s\n", message->sender->name, message->content);
        }
    }
}

Post* new_post(User* user, const char* content) {
    if (!user) return NULL;
    Post* post = (Post*)malloc(sizeof(Post));
    post->post_id = post_id_counter++;
    post->user = user;
    strcpy(post->content, content);
    post->likes = 0;
    all_posts[post_count++] = post;
    return post;
}

void add_like(Post* post, User* user) {
    if (!post || !user || !is_friend(post->user, user)) return;
    post->likes++;
}

void display_feed(User* user) {
    Post* feed[MAX_FEED];
    int count = 0;

    // Collect posts from user and friends
    for (int i = 0; i < post_count; i++) {
        Post* post = all_posts[i];
        if (post->user == user || is_friend(user, post->user)) {
            feed[count++] = post;
            if (count == MAX_FEED) break;
        }
    }

    // Sort posts by likes (desc) and recency (FIFO)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (feed[i]->likes < feed[j]->likes || 
               (feed[i]->likes == feed[j]->likes && feed[i]->post_id > feed[j]->post_id)) {
                Post* temp = feed[i];
                feed[i] = feed[j];
                feed[j] = temp;
            }
        }
    }

    // Print feed strictly aligned with the output format
    for (int i = 0; i < count; i++) {
        printf("[%s:] %s", feed[i]->user->name, feed[i]->content);
        if (i < count - 1) printf(","); // Ensure no trailing space after commas
    }
    printf("\n");
}
