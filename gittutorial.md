https://missing.csail.mit.edu/2020/version-control/



Notes:
#Git notes

Who wrote module, who add, which commit, when

Broken code, regression was introduced, identifiece what made code to broke.

##Comic

You dont have to do this anymore

Learning git 

git internals and data models to be understood

floders : Top level things called - Trees
files called	                  - Blobs

Snapshots - state 1 <- 2 <- 3 

type blob = array <bytes>
type tree = map<string, tree | blob>
type commits = struct {
			para array <commit>
			author string 
			message string
			snapshot tree }
type obj blob | tree | commit
obj = map<string, object>

Hash func : Big piece of data makes the small name for it

Git implemented in C bash and etc..


object and references

Git commands

turn the folder into git 
- git init
- git help ex git help init
- git status 
create a file
make a new snapshot 
- staging area, tell git what to be included in next snapshot
- git add <file>
- git commit 
Creates a hash of commit
sha1 HASH, 
- git log, visualize the version flatten history
- git cat-file -p hash
- git log --all --graph --decorate --oneline ->looks better
- master most up to date versio of project
- name HEAD - where your corrently looking right now
- git checkout -> 
- git checkout <commithash>
- git diff <hash> <filename>
Branching and merging
- git status 
- git add
- git commit
- git branch -> list local branch
- git branch -vv
- git branch cat
- git branch <brname>; git checkout <brname>
checkout between backandforth in branch
- git merge <brname> 
- git mergetool
- git merge --abort
- git add <fname>
- git merge --continue


- git remote, list of all remote repos
- git push origin master:master
- git log --all --graph --decorate --oneline
What remote coorresponding to repo
- git branch --set-upstream-to=origin/master
- git branch -vv
retrieve changes 
- git fetch 
- git log
- git pull
- git remote
- git fetch
- git merge
- git pull (fetch and merge)

other things to git

- git config , vin ~/.gitconfig
- git clone --shallow , only for latest snapshot
- git diff
- git add -p <fname> , interactive staging
- git diff --cached
- git blame <fname> , who made changes to line
- git stash , revert the working dir saves temp
- git stash pop
- git bisect, manually search history for something finding out unittest file checking, binary search the history, give the unit test where it is failing
- vim .gitignore , specify the file name


- graphical clients
- shell integration
- integration with vim







