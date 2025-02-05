# Objective
SHA-1 (Secure Hash Algorithm 1) is a cryptographic hash function that produces a 160-bit hash value. It was widely used for data integrity and digital signatures, although it is now considered insecure for most cryptographic purposes due to vulnerabilities to collision attacks.

# Algorithm
1. Pre-processing:
   - Append a single bit "1" to the message.
   - Append "0" bits until the message length (in bits) is congruent to 448 modulo 512.
   - Append the original message length as a 64-bit big-endian integer.
2. Initialize hash values:
   - Set five 32-bit variables (H0, H1, H2, H3, H4) to specific constants.
3. Process the message in 512-bit blocks:
   - Divide the message into 512-bit blocks.
   - For each block, perform the following steps:
       a. Divide the block into 16 words of 32 bits each.
       b. Extend the 16 words into 80 words using bitwise operations.
       c. Perform 80 rounds of processing using logical functions, constants, and bitwise operations.
4. Output:
   - Concatenate the hash values (H0, H1, H2, H3, H4) to produce the final 160-bit hash value.

# Explanation
SHA-1 processes the input message in chunks of 512 bits. Each chunk undergoes a series of transformations to produce a unique 160-bit hash value. The algorithm uses logical functions, modular addition, and bitwise operations to ensure the hash is unique to the input message.
Although SHA-1 is no longer recommended for secure cryptographic applications, it is still used in legacy systems and for non-critical data integrity checks.
