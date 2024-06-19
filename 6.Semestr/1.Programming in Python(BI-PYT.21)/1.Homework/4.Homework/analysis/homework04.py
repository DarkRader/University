"""
In this homework, we will use well-known Titanic dataset which contains 
information about passengers of Titanic. The dataset consists of personal 
information about each passenger and indicator whether the passenger 
survived. We will use this data to analyse passenger list and their chance for
survival.

The provided dataset contains the following attributes:
 'Age' - age in years,
 'Fare' - fare ticked price,
 'Name' - passenger name,
 'Parch' - # of parents/children of a person on board,
 'PassengerId' - identifier,
 'Pclass' - travelling class, 1 = 1. class, 2 = 2. class, 3 = 3. class,
 'Sex' - sex,
 'SibSp' - # siblings/spouses on board,
 'Survived' - 0 = died, 1 = survived,
 'Embarked' - boarding port C = Cherbourg, Q = Queenstown, S = Southampton,
 'Cabin' - cabin number
 'Ticket' - ticket number
"""

import pandas as pd
import numpy


def load_dataset(train_file_path: str, test_file_path: str) -> pd.DataFrame:
    """
    Write a function which loads CSV from two files to pandas DataFrame and
    performs several data processing steps. Use data provided in `data`
    directory for testing ('data/train.csv' as input parameter
    `train_file_path`, and 'data/test.csv'  as `test_file_path`). Add column
    name "Label" to each DataFrame. The column should contain value "Train"
    for data from `train_file_path` and "Test" from test_file_path.
    
    Perform following operations with DataFrames (keep the order of the
    operations):
        1. Concatenate both DataFrames.
        2. Remove columns  "Ticket", "Embarked", "Cabin" from created DataFrame.
        3. Set the index to unique numbers from zero to the number of rows.

    The return value of the function is processed DataFrame.
    """

    train_data = pd.read_csv(train_file_path)
    test_data = pd.read_csv(test_file_path)

    train_data['Label'] = 'Train'
    test_data['Label'] = 'Test'

    # Concatenate both DataFrames.
    join_data = pd.concat([train_data, test_data], ignore_index=True)

    # Remove columns  "Ticket", "Embarked", "Cabin" from created DataFrame.
    join_data.drop(columns=['Ticket', 'Embarked', 'Cabin'], inplace=True)

    # Set the index to unique numbers from zero to the number of rows.
    join_data.reset_index(drop=True, inplace=True)

    return join_data


def get_missing_values(df: pd.DataFrame) -> pd.DataFrame:
    """
    When working and analysing data, one often needs to deal with missing
    values. For example, some passengers did not fill information about
    family members. In that case, one needs to be aware of it as it may
    introduce bias to the data.

    Write a function which determines the number of missing values in given
    DataFrame. The function should output a new DataFrame. The new DataFrame
    should be indexed by columns of original DataFrame. Columns of returned
    DataFrame will be (keep the order of the columns):
        1. "Total" - contains the number of missing values
        2. "Percent" - contains the percentage of missing values with regard to all
        rows of given DataFrame.

    Sort the resulting DataFrame based on the number of missing values from
    largest to smallest.
    
    Example of output:

               |  Total  |  Percent
    "Column1"  |   34.5  |    76.54321
    "Column2"  |   0     |    0
    """

    sum_missing = df.isnull().sum()

    percent_missing = (sum_missing / len(df)) * 100

    # 1. "Total" - contains the number of missing values.
    # 2. "Percent" - contains the percentage of missing values with regard to all rows of given DataFrame.
    missing_data = pd.DataFrame({'Total': sum_missing, 'Percent': percent_missing})

    # Sort the resulting DataFrame based on the number of missing values from largest to smallest.
    missing_data = missing_data.sort_values(by='Total', ascending=False)

    return missing_data


def substitute_missing_values(df: pd.DataFrame) -> pd.DataFrame:
    """
    One way how to handle missing data is to substitute missing values with
    some statistic of other rows. We will use this method for two columns:
        1. "Age" - fill missing values with the mean of other rows.
        2. "Fare" - fill missing values with the lowest price of ~$15 (we
        suppose that the majority of unregistered tickets were the cheapest
        ones).

    Do not to modify given DataFrame but create a copy of it.
    """

    # Copy of given DataFrame.
    data = df.copy()

    # "Age" - fill missing values with the mean of other rows.
    data['Age'].fillna(df['Age'].mean(), inplace=True)

    # "Fare" - fill missing values with the lowest price of ~$15.
    data['Fare'].fillna(15, inplace=True)

    return data


def get_correlation(df: pd.DataFrame) -> float:
    """
    We want to know whether there is a relationship between the age of a
    passenger and fare ticket price (e.g. younger children have cheaper
    tickets). We will use Pearson correlation coefficient to quantify linear
    relationship between columns "Age" and "Fare".
    The result will be returned as one number.

    Pearson correlation coefficient quantifies linear relationship between
    two random variables. Correlation ranges from -1 to 1. Value around zero
    indicates no linear relationship, -1 indicates strong negative
    relationship, 1 indicates strong relationship.
    """

    return df['Age'].corr(df['Fare'])


def get_survived_per_class(df: pd.DataFrame,
                           group_by_column_name: str) -> pd.Series:
    """
    We want to know how big was the chance of survival for different groups of
    passengers (e.g. for different sexes, classes, etc.). Write a function
    that estimates that. The input of the function is a DataFrame with data
    and name of column (group_by_column_name) which holds group information.
    To increase readability of the result sort values from the highest chance of
    survival to lowest and round the resulting values to 2 decimal places.
    Return result as pandas Series.
    
    Example:

    get_survived_per_class(df, "Sex")

                  Survived
    Female     |      0.82
    Male       |      0.32

    """

    # Implement your own solution.
    survived_group = df.groupby(group_by_column_name)['Survived'].mean()

    # Sort values from the highest chance of survival to lowest.
    survived_group_sort = survived_group.sort_values(ascending=False)

    # Round the resulting values to 2 decimal places.
    survived_group_sort = survived_group_sort.round(2)

    return survived_group_sort


def get_outliers(df: pd.DataFrame) -> (int, pd.DataFrame):
    """
    We want to explore fare ticket prices. An important part of such
    exploration is exploration of outliers. An outlier may indicate an error
    in the data (somebody entered price incorrectly) or some special group of
    passengers.

    We will use the IQR method for the identification of outliers. IQR method
    considers an outlier any point which does not fulfil:
        Q1 - 1.5*IQR < point_value < Q3 + 1.5*IQR,
    where Q1 and Q3 are the first and the third quartiles respectively
    calculated from all points in data. IQR is the inter-quartile range
    calculate as the difference between Q3 and Q1:
        IQR = Q3 - Q1.

    Return tuple with the number of outliers and all passengers with outlier
    fare ticket price.
    """

    Q1 = df['Fare'].quantile(0.25)
    Q3 = df['Fare'].quantile(0.75)
    IQR = Q3 - Q1

    # Use the IQR method for the identification of outliers.
    min_value = Q1 - 1.5 * IQR
    max_value = Q3 + 1.5 * IQR
    outliers_data = df[(df['Fare'] < min_value) | (df['Fare'] > max_value)]

    # The number of outliers.
    outliers_number = outliers_data.shape[0]

    return outliers_number, outliers_data


def create_new_features(df: pd.DataFrame) -> pd.DataFrame:
    """
    To analyse data and use them for modeling, it may be convenient to create
    a new columns (features). These new features are usually created
    transformation of original values. For example, if we want to compare
    survivals from Titanic and SS Eastland we will want to scale fare prices
    to the same values for each ship as travelling on Titanic was more
    expensive.

    Create 3 new variables:
        1. "Fare_scaled" - scale "Fare" columns to have zero mean and standard
       deviation equal one.
        2. "Age_log" - is natural logarithm of attribute "Age" (differences
        between age of children are magnified in comparison to adults).
        3. "Sex" -  Replace string values with numerical ones, where "male"
        will be replaced with 0 and "female" with 1. The resulting values
        should have type `int`.

    Do not modify original DataFrame.
    """

    # Copy of given DataFrame
    data = df.copy()

    # "Fare_scaled" - scale "Fare" columns to have zero mean and standard deviation equal one.
    data['Fare_scaled'] = (data['Fare'] - data['Fare'].mean()) / data['Fare'].std()

    # "Age_log" - is natural logarithm of attribute "Age".
    data['Age_log'] = numpy.log(data['Age'])

    # "Sex" -  Replace string values with numerical ones, where "male" will be replaced
    # with 0 and "female" with 1. The resulting values should have type `int`.
    data['Sex'] = data['Sex'].map({'male': 0, 'female': 1}).astype(int)

    return data


def determine_survival(df: pd.DataFrame, n_interval: int, age: float,
                       sex: str) -> float:
    """
    Determine the probability of survival of a person specified by age and sex.

    Use only the data with the label "Train". Missing values in column "Age" replace with mean value. In order to
    moderate significance of the estimated probability, divide "Age" to
    specified number of intervals and calculate probability from given
    interval. For example if we have values in "Age" column [2, 13, 18, 25] and
    we want 2 intervals, result should be:

    0        (2, 13.5]
    1     (13.5, 25.0]

    With division based on "Sex", the categorization should be:

       "AgeInterval" | "Sex"       |   "Survival Probability"
       (1.977, 13.5] | "male"      |            0.21
       (1.977, 13.5] | "female"    |            0.28
       (13.5, 25.0]  | "male"      |            0.10
       (13.5, 25.0]  | "female"    |            0.15

    Output of determine_survival(df, n_interval=2, age = 5, sex = "male")
    should be 0.21. If there is no passenger for some group, return numpy
    NA value.
    """

    # Use only the data with the label "Train".
    train_data = df[df['Label'] == 'Train']

    # Missing values in column "Age" replace with mean value.
    train_data['Age'].fillna(train_data['Age'].mean(), inplace=True)

    # Divide "Age" to specified number of intervals and calculate probability from given interval.
    age_intervals = pd.cut(train_data['Age'], bins=n_interval)

    # Group by "AgeInterval" and "Sex" and calculate survival probability.
    train_data_group = train_data.groupby([age_intervals, 'Sex'])['Survived'].mean()

    if (age, sex) in train_data_group.index:
        # Determine the probability of survival of a person specified by age and sex.
        return train_data_group[age][sex]

    # If there is no passenger for some group, return numpy NA value
    return numpy.nan
