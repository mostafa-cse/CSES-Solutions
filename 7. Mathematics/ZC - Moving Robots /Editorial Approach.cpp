#include <bits/stdc++.h>
using namespace std;
const int N = 8;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int k;
    cin >> k;

    // dp[r][c] will store the probability that the CURRENT robot being simulated
    // is at position (r, c) after a certain number of steps.
    double dp[N][N];
    double next_dp[N][N];

    // empty_prob[r][c] stores the probability that square (r, c) remains EMPTY
    // after considering all robots so far.
    // Initialize to 1.0 because initially (with 0 robots considered),
    // the probability of a square being empty is 100%.
    double empty_prob[N][N];
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            empty_prob[i][j] = 1.0;
        }
    }

    // Direction vectors for moving: Right, Left, Down, Up
    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    // Iterate through every possible starting position (every robot)
    for (int start_row = 0; start_row < N; ++start_row) {
        for (int start_col = 0; start_col < N; ++start_col) {

            // --- STEP 1: Run DP for the robot starting at (start_row, start_col) ---

            // Reset DP table for this specific robot
            for(int i = 0; i < N; ++i)
                for(int j = 0; j < N; ++j)
                    dp[i][j] = 0.0;

            // The robot starts here with 100% probability
            dp[start_row][start_col] = 1.0;

            // Simulate k steps
            for (int step = 0; step < k; ++step) {
                // Clear the next_dp buffer
                for(int i = 0; i < N; ++i)
                    for(int j = 0; j < N; ++j)
                        next_dp[i][j] = 0.0;

                // For every square, distribute its probability to neighbors
                for (int r = 0; r < N; ++r) {
                    for (int c = 0; c < N; ++c) {
                        // check that is there any robots
                        if (dp[r][c] > 0.0) {
                            // First, calculate how many valid moves exist from this square
                            int valid_moves = 0;
                            for (int d = 0; d < 4; ++d) {
                                int nr = r + dr[d];
                                int nc = c + dc[d];
                                if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                                    valid_moves++;
                                }
                            }

                            // Distribute the probability equally among valid moves
                            double prob_per_move = dp[r][c] / valid_moves;

                            for (int d = 0; d < 4; ++d) {
                                int nr = r + dr[d];
                                int nc = c + dc[d];
                                if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
                                    next_dp[nr][nc] += prob_per_move;
                                }
                            }
                        }
                    }
                }

                // Update dp table for the next step
                for(int i = 0; i < N; ++i)
                    for(int j = 0; j < N; ++j)
                        dp[i][j] = next_dp[i][j];
            }

            // --- STEP 2: Update the global empty_prob grid ---

            // After k steps, 'dp[r][c]' is the probability that the robot
            // starting at (start_row, start_col) ends up at (r, c).
            // Therefore, (1.0 - dp[r][c]) is the probability it does NOT land there.
            for (int r = 0; r < N; ++r) {
                for (int c = 0; c < N; ++c) {
                    empty_prob[r][c] *= (1.0 - dp[r][c]);
                }
            }
        }
    }

    // --- STEP 3: Sum the expectations ---
    double expected_empty_squares = 0.0;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            expected_empty_squares += empty_prob[r][c];
        }
    }

    // Output formatted to 6 decimal places as required
    cout << fixed << setprecision(6) << expected_empty_squares << endl;

    return 0;
}
