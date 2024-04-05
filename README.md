# Search-Engine-Project

**Project 2 - Search Overview**


In this project, I look on C++ data structures, specifically sets and maps, to construct a document search engine capable of handling complex queries. By the project's completion, students will have implemented a robust search engine that supports various search queries and gained valuable experience with essential C++ data structures. Key features include preprocessing body text, storing data in efficient data structures, and executing search queries effectively.

**Search Engines:**
The search engine operates on web page data consisting of unique URLs and their corresponding body text. We preprocess the body text and organize it into a data structure optimized for fast query and retrieval. The engine allows users to pose questions such as identifying pages containing specific keywords, combinations of keywords, or complex search queries involving modifiers like + and -.

**Restrictions:**
To ensure efficient and effective coding practices, certain restrictions are in place:
- Use standard C++ libraries only, without incorporating external libraries.
- Avoid the use of structs, pointers, new, or malloc.
- Refrain from adding global variables; instead, define them in main and utilize pass-by-reference.
- Maintain provided function signatures without alterations.
- Emphasize function decomposition and manage program complexity, avoiding excessive nested loops.

**Testing:**
The significance of testing in ensuring code correctness is emphasized. Students are encouraged to write comprehensive test suites to evaluate their code's behavior, covering various scenarios and edge cases. Both public and hidden tests are employed to assess code functionality and test coverage accurately.

**Tasks:**
The project is divided into multiple tasks, each focusing on specific functionalities and implementations:
1. CleanToken: Preprocess individual tokens from text, adhering to specified cleaning criteria.
2. GatherTokens: Extract unique tokens from text and prepare them for indexing.
3. BuildIndex: Create an inverted index mapping tokens to corresponding web page URLs.
4. FindQueryMatches: Utilize the inverted index to match search queries and retrieve relevant page URLs.
5. SearchEngine: Integrate all components to create a functional search engine, capable of processing queries and delivering results.

**Conclusion:**
Project 2 offers students a hands-on opportunity to apply C++ data structures in practical scenarios, reinforcing fundamental concepts while honing problem-solving and coding skills. Through iterative development, rigorous testing, and adherence to coding standards, students gain valuable insights into software engineering principles and practices.
