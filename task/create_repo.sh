#!/bin/sh -x

ROOT_DIR=$(dirname $0)/..

cd ${ROOT_DIR}

REPO_NAME=$(basename ${PWD})

# create a github repository
gh auth status
gh repo create ${REPO_NAME} --public

OWNER=$(gh repo list --json owner -q '.[0].owner.login')

# create a local repository and set origin
git init
git remote add origin https://github.com/${OWNER}/${REPO_NAME}.git

# initial commit
git add .
git commit -a -m "initial commit"
git push -u origin main
