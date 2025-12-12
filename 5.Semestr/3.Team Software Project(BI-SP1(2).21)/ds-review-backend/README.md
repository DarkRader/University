# Wizview - Data Stewardship Review

***

## TL;DR 💨:

### Run using **docker** 🏗:

> 1) run `$ docker compose up` 🏗
> 2) after docker compose finishes and runs up containers, go to http://localhost:8000/
> 3) enjoy the app ✨ (if there are some problems - see **troubleshoots** 🔥🚒 section of this readme file)
> 4) run `$ docker compose exec backend bash`
> 5) run `$ source /venv/bin/activate` to activate virtual environment
> 6) run `$ cd app/`
> 7) run `$ ./scripts/run_tests.sh` to run tests.
> 8) run `$ ./scripts/pep8_pylint.sh` to run pylinter.
> 9) run `$ ./scripts/mypy` to run mypy.

### Run using **mamba**🐍(faster and smaller than conda):

Installing mamba:

> 1) Follow official installation guide  https://mamba.readthedocs.io/en/latest/installation.html

Running using mamba:

> 1) using mamba install conda-lock package, running `$ mamba install conda-lock` 
> 2) in the project root run `$ ./scripts/create_or_update_env.sh` to create ds-review environment to run the
     application
> 3) run `$ mamba activate ds-review` to activate new installed environment
> 4) run `$ docker compose up db` to run postgresql database
> 5) run `$ cd app/app/` and then `$ python -m main` to start application
> 6) go to http://localhost:8000/ and enjoy the app ✨
> 7) run `$ cd ../` and then `$ ./scripts/run_tests.sh -c` to run tests with coverage.
> 8) run `$ ./scripts/pep8_pylint.sh` to run pylinter.
> 9) run `$ ./scripts/mypy.sh` to run mypy.

### Run using **conda** 🐍:

Installing conda:

> 1) Follow official installation guide  https://docs.conda.io/projects/conda/en/latest/user-guide/install/index.html
> 2) It is recommended to install Miniconda, because it will take less disk space.

Running using conda:

> 1) using conda install conda-lock package, running `$ conda install conda-lock` 
> 2) in the project root run `$ ./scripts/create_or_update_env.sh` to create ds-review environment to run the
     application
> 3) run `$ conda activate ds-review` to activate new installed environment
> 4) run `$ docker compose up db` to run postgresql database
> 5) run `$ cd app/app/` and then `$ python -m main` to start application
> 6) go to http://localhost:8000/ and enjoy the app ✨
> 7) run `$ cd ../` and then `$ ./scripts/run_tests.sh -c` to run tests with coverage.
> 8) run `$ ./scripts/pep8_pylint.sh` to run pylinter.
> 9) run `$ ./scripts/mypy.sh` to run mypy.

***

## Pylint

We use pylint to check quality of our code. There is a script to run pylint on the whole codebase.
To run it just run the script:

```shell
 $ ./scripts/pep8_pylint.sh
```

There can be situation where pylint is wrong, but we can avoid it by using comments for pylint,
which tell it to disable warning.

```python
# some code without warnings ...

# here we want to disable warning with the name no-self-argument:
# pylint: disable=no-self-argument
# reason: pydantic validator doesn't work with self argument.

# some code which causes the warning...

# pylint: enable=no-self-argument

# some code without warnings ...

```

Also we have the `.pylintrc` file, which stores global settings for pylinter, for example good names:

```
# Good variable names which should always be accepted
# Pylinter will not give warnings to these short names
good-names=i, j, df, db
```

***

## Useful links

- FastAPI [documentation](https://fastapi.tiangolo.com/tutorial/sql-databases/).

***

## Troubleshoots 🔥🚒:

- Make sure you run commands from appropriate directory. If you run scripts, run them in the directory where the
  **scripts/** directory lies, not inside the **scripts/** directory.
- If you have problems with **conda**, try to run `$ ./scripts/set_up_conda_channels.sh` in the project root to add
  conda-forge channel to conda. Then try to create conda environment again.
- If you have problems with **docker compose**, be sure you run newer `docker compose` tool instead of
  older `docker-compose`

***

