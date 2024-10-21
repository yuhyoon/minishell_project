git checkout hyeyeom 
해서

git branch 
해서 현재 브랜치가 hyeyeom으로 되어있는지 확인하고 작업하면 돼

gkdlgkdlgkl
hyeyeom 브랜치 삭제!

https://graphite.dev/guides/managing-deleted-branches-in-github
Ensure you are not on the branch you want to delete: Switch to a different branch, typically the main branch:
TERMINAL
git checkout main


Delete the branch locally: Use the git branch -d <branch-name> command for a safe deletion that checks for unmerged changes, or git branch -D <branch-name> to force the deletion:
TERMINAL
git branch -d feature-branch


Push the deletion to GitHub: To remove the branch from your remote GitHub repository, use:
TERMINAL
git push origin --delete feature-branch

Recovering a deleted branch
If you remember the commit hash that was the tip of your deleted branch, you can recover it:

Find the last commit of the deleted branch: If you don’t remember the commit hash, you can find it using:
TERMINAL
git reflog


This command shows a log of where your HEAD and branch pointers have been recently, including at the time you deleted the branch.
Create a new branch from the old commit: Once you have the commit hash, create a new branch pointing to it:
TERMINAL
git checkout -b new-branch-name <commit-hash>


Deleting branches in GitHub helps keep your repository clean and manageable, especially after features have been merged or ideas abandoned. Although deleting a branch removes its reference, the commits generally remain accessible, allowing for recovery if necessary. This flexibility ensures that you can manage your project effectively without losing important work.

https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-and-deleting-branches-within-your-repository#deleting-a-branch