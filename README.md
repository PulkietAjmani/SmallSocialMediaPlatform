# SmallSocialMediaPlatform
Social Media Platform – C Implementation

This project implements a simplified social media platform in C, featuring user management, friendships, messaging, posting, and feed display. It showcases the use of key data structures such as arrays and queues to manage dynamic social interactions.

🚀 Features

👤 User Profile Management

Create and delete user profiles

Update username and email

Add or remove friends

Display users and friends in alphabetical order

🔍 Search Functionality

Search users by username or email

👥 Mutual Friends

Retrieve and display mutual friends between two users

💬 Messaging System

Send and receive direct messages (between friends only)

Maintain chat history using a FIFO queue (up to 50 messages per user pair)

Display formatted conversation history

📝 Posts & Likes

Users can create posts (up to 256 characters)

Friends can like posts (one like per user per post)

View number of likes per post

📰 Feed Generation

Display up to 20 most recent posts from user and friends

Feed sorted by number of likes (descending), then post age (oldest first)
