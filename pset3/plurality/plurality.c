#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
void merge_sort(candidate array[], int start, int end);
void merge(candidate array[], int start, int mid, int end);
void print_candidates();

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes += 1;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    merge_sort(candidates, 0, candidate_count - 1);

    if (candidates[0].votes != 0)
    {
        printf("%s\n", candidates[0].name);
        int i = 1;
        while (candidates[0].votes == candidates[i].votes)
        {
            printf("%s\n", candidates[i++].name);
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
        if (Left[l].votes >= Right[r].votes)
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

// Print All Candidate Data from candidates[]
void print_candidates()
{
    printf("%s\t\t%s\n", "Name", "Count");
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%s\t\t%d\n", candidates[i].name, candidates[i].votes);
    }
}