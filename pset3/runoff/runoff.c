#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
int binary_search(candidate array[], int start, int end, string key);
void merge_sort(candidate array[], int start, int end);
void merge(candidate array[], int start, int mid, int end);
void print_candidates();


int main(int argc, string argv[])
{

    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }



    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    int count = 0;

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();

        bool tie = is_tie(min);


        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }

    return 0;

}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    merge_sort(candidates, 0, candidate_count - 1);
    int result = binary_search(candidates, 0, candidate_count - 1, name);

    if (result != -1)
    {
        preferences[voter][rank] = result;
        return true;
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    {
        for(int j = 0; j < candidate_count; j++)
        {
            int preference = preferences[i][j];
            if (!candidates[preference].eliminated)
            {
                candidates[preference].votes ++;
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{

    for (int i = 0; i < candidate_count; i++)
    {
        // If candidate has more than half of the vote, print the name and return true
        if(candidates[i].votes > voter_count / 2 && !candidates[i].eliminated)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Set number of vote from first candidate as minimum
    int min = candidates[0].votes;

    for(int i = 0; i < candidate_count; i++)
    {
        if(min > candidates[i].votes && !candidates[i].eliminated)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{

    for (int i = 0; i < candidate_count; i++)
    {
        // If the number of votes is not minimum and not eliminted return false
        if (candidates[i].votes != min && !candidates[i].eliminated)
        {
            return false;
        }
    }

    return true;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // If number of vote from the candidate is minimun, then return true
        if (candidates[i].votes == min && !candidates[i].eliminated)
        {
            candidates[i].eliminated = true;
        }
    }

    return;
}

// 1. Get middle value of the array.
// 2. Divide into two halves.
// 3. Merge two halves into one.
void merge_sort(candidate array[], int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        merge_sort(array, start, mid);
        merge_sort(array, mid + 1, end);
        merge(array, start, mid, end);
    }
}

// 1. Copy Data into Temp arrays: Left & Right.
// 2. Compare Two Sub Arrays and merge into parent array.
// 3. Copy and merge data from remaining array from temp arrays.
void merge(candidate array[], int start, int mid, int end)
{

    int left = mid - start + 1;
    int right = end - mid;
    candidate Left[left], Right[right];

    // 1. Copy Data into Temp arrays: Left & Right.
    for (int i = 0; i < left; i++)
    {
        Left[i] = array[start + i];
    }

    for (int i = 0 ; i < right; i++)
    {
        Right[i] = array[mid + 1 + i];
    }


    // 2. Compare Two Sub Arrays and merge into parent array.
    int l = 0, r = 0;
    int i = start;
    while (l < left && r < right)
    {
        // if (Left[l].name >= Right[r].name)
        if (strcmp(Left[l].name, Right[r].name) <= 0)
        {
            array[i++] = Left[l++];
        }
        else
        {
            array[i++] = Right[r++];
        }
    }


    // 3. Copy and merge data from remaining array from temp arrays.
    while (l < left)
    {
        array[i++] = Left[l++];
    }

    while (r < right)
    {
        array[i++] = Right[r++];
    }
}

int binary_search(candidate array[], int start, int end, string key)
{
    if (start <= end)
    {
        int middle = (start + end) / 2;

        if (strcmp(array[middle].name, key) == 0)
        {
            return middle;
        }
        else if (strcmp(array[middle].name, key) > 0)
        {
            return binary_search(array, start, middle - 1, key);
        }
        else
        {
            return binary_search(array, middle + 1, end, key);
        }
    }

    return -1;
}
