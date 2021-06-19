#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int get_strength(pair index);
int binary_search(string array[], int start, int end, string key);
bool is_cycle(int idx, bool visited[]);
bool is_winner(int idx);
void sort_candidates(int left, int right);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    sort_candidates(0, candidate_count - 1);

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);
            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    int result = binary_search(candidates, 0, candidate_count - 1, name);

    if (result != - 1)
    {
        ranks[rank] = result;
        return true;
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }
        }
    }

    // // // Testing for Preferences
    // printf("\nPreferences\n");
    // for(int i = 0; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         printf("[%d] ", preferences[i][j]);
    //     }
    //     printf("\n");
    // }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++){
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    // Testing Pairs
    // printf("Unsorted\n");
    // for (int i = 0; i < pair_count; i++){
    //     // printf("%s-%s\t%d\n", candidates[pairs[i].winner], candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser]);
    //     // printf("%s-%s\t%d\n", candidates[pairs[i].winner], candidates[pairs[i].loser], get_strength(i));
    //     printf("%s-%s\t%d-%d\t%d\n", candidates[pairs[i].winner], candidates[pairs[i].loser],
    //                                  preferences[pairs[i].winner][pairs[i].loser],
    //                                  preferences[pairs[i].loser][pairs[i].winner],
    //                                  get_strength(pairs[i]));
    // }
    // printf("\n");


    return;
}

int get_strength(pair idx)
{
    return preferences[idx.winner][idx.loser] - preferences[idx.loser][idx.winner];
}


// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // // Insertion Sort
    for (int i = 1; i < pair_count; i++)
    {
        pair idx = pairs[i];
        int j = i - 1;

        while (j >= 0 && get_strength(pairs[j]) < get_strength(idx))
        {
            pairs[j + 1] = pairs[j];
            j = j - 1;
        }
        pairs[j + 1] = idx;

    }

    // // Testing
    // printf("Sorted\n");
    // for (int i = 0; i < pair_count; i++){
    //     // printf("%s-%s\t%d\n", candidates[pairs[i].winner], candidates[pairs[i].loser], preferences[pairs[i].winner][pairs[i].loser]);
    //     printf("%s-%s\t%d-%d\t%d\n", candidates[pairs[i].winner], candidates[pairs[i].loser],
    //                                  preferences[pairs[i].winner][pairs[i].loser],
    //                                  preferences[pairs[i].loser][pairs[i].winner],
    //                                  get_strength(pairs[i]));
    // }
    // printf("\n");

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        bool visited[candidate_count];
        for (int j = 0; j < candidate_count; j++)
        {
            visited[j] = false;
        }

        if (is_cycle(pairs[i].winner, visited))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }

    }

    // // Testing
    // printf("Locked Pairs\n");
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for (int j = 0; j < candidate_count; j++)
    //     {
    //         printf("%d", locked[i][j]);
    //     }
    //     printf("\n");
    // }

    return;
}


bool is_cycle(int idx, bool visited[])
{

    //
    if (visited[idx])
    {
        return true;
    }

    // Mark the node as visited
    visited[idx] = true;

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[idx][i] && is_cycle(i, visited))
        {
            return true;
        }
    }

    return false;

}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (is_winner(i))
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}

bool is_winner(int idx)
{
    // Winner if the column's values in locked[] are zero.
    // For example  A  B  C
    //              0  1 [0]
    //              0  0 [0]
    //              1  0 [0] So C is the winner

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][idx])
        {
            return false;
        }
    }
    return true;
}

// Quick Sort algorithm will be applied.
void sort_candidates(int left, int right)
{
    if (left >= right)
    {
        return;
    }

    // Middle will be set as Pivot
    int middle = (left + right) / 2;
    string pivot = candidates[middle];

    int l = left, r = right;
    while (l <= r)
    {
        // If pivot is greater than Left Index; go to Right
        // while (pivot > array[l])
        while (strcmp(candidates[l], pivot) < 0)
        {
            l++;
        }
        // If pivot is less than Right Index, go to Left
        // while (pivot < array[r])
        while (strcmp(candidates[r], pivot) > 0)
        {
            r--;
        }
        // Swap Two Arrays
        if (l <= r)
        {
            string temp = candidates[l];
            candidates[l] = candidates[r];
            candidates[r] = temp;
            l++;
            r--;
        }
    }

    // Sort recursively until Right Index reach to start point
    if (left < r)
    {
        sort_candidates(left, r);
    }
    // Sort recusively until Left Index reach to end point
    if (right > l)
    {
        sort_candidates(l, right);
    }
}

int binary_search(string array[], int start, int end, string key)
{
    if (start <= end)
    {
        int middle = start + (end - start) / 2;

        // If the key is matched, return the middle.
        if (strcmp(array[middle], key) == 0)
        {
            return middle;
        }
        // If the key is greater than the middle, go to Left
        else if (strcmp(array[middle], key) > 0)
        {
            return binary_search(array, start, middle - 1, key);
        }
        // If the key is less than the middle, go to Right
        else if (strcmp(array[middle], key) < 0)
        {
            return binary_search(array, middle + 1, end, key);
        }
    }
    return -1;
}
