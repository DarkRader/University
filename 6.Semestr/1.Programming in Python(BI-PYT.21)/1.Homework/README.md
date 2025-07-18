# BI-PYT

## How to start
-  Create and add SSH keys to your gitlab profile ( link:https://colab.research.google.com/drive/1VdQusn_rgabFx4uy1jsqzRexaVl5nZiO#scrollTo=S5gLPsNGrUNI[See tutorial #1]).
-  Prepare a directory for BI-PYT, eg. `mkdir bi-pyt` and jump in `cd bi-pyt`.
-  Clone this repository: `git clone git@gitlab.fit.cvut.cz:BI-PYT/B232/{your-login}.git`
-  Create a virtual environment: `python3.11 -m venv venv-bipyt`
-  Activate the venv: `source venv-bi-pyt/bin/activate`
-  Jump in your materials: `cd {your-login}`
-  Install all required python packages `pip install -r requirements.txt`
-  Run jupyter notebook `jupyter notebook`

## Each laboratory

At the beginning of the laboratory, pull assignments and create a new branch in which you will work.

. Switch to master branch `git checkout master`
. Pull assigments `git pull`
. Create a new branch for laboratory `git checkout -b branch_name`
. Activate the environment `source ../venv-bi-pyt/bin/activate`
. Run jupyter notebook `jupyter notebook`

After the lab, we recommend you to save your code to gitlab.

```
git status # show changes
git add your_lab_notebook.ipynb # add file(s) to the staging area
git commit -m 'Message' # commit the changes to the local repositort
git push origin branch_name # push changes to remote repository
```

## Homeworks

There is a separate folder for each homework. Each homework has a set of attached unit tests. You can run these tests locally by executing command `pytest` inside of the homework folder. The pytest package has been also added to the virtual environment.

Similar to each laboratory create a **special branch** for each homework and name it `homeworkXX`, where XX is zero padded number of the homework (e.g. homework01). The branch naming is important because of automated testing on Gitlab. If you don't name the branch correctly, tests will not be executed by the CI and the homework solution will not be accepted. If you creating a new branch as a copy of `master`, **you have to delete all irrelevant content like other homeworks and all tutorials**; or you can use `git switch --orphan homeworkXX`.

After the homework is finished, commit and push your homework branch to faculty Gitlab.
