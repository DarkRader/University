package cz.cvut.kuznear1.tweenapp.ui.screen

import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.tooling.preview.Preview
import cz.cvut.kuznear1.tweenapp.R

@Preview
@Composable
fun EmptyScreen(modifier: Modifier = Modifier) {
    Box(
        modifier = modifier.fillMaxSize(),
    ) {
       Text(
           modifier = Modifier.align(Alignment.Center),
           text = stringResource(R.string.there_are_no_tweets_yet),
           style = MaterialTheme.typography.bodyLarge
       )
    }
}