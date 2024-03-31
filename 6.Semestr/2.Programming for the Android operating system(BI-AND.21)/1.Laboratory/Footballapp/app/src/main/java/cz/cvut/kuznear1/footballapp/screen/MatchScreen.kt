package cz.cvut.kuznear1.footballapp.screen

import android.graphics.Paint.Align
import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.Spacer
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.material3.Button
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.getValue
import androidx.compose.runtime.mutableIntStateOf
import androidx.compose.runtime.mutableStateOf
import androidx.compose.runtime.remember
import androidx.compose.runtime.setValue
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import cz.cvut.kuznear1.footballapp.R
import cz.cvut.kuznear1.footballapp.Screens


@Composable
fun MatchScreen(navController: NavController) {
    var leftScore by remember {  mutableIntStateOf(0) }
    var rightScore by remember {  mutableStateOf(0) }

    Column(modifier = Modifier.fillMaxSize().padding(40.dp),
        horizontalAlignment = Alignment.CenterHorizontally,
        verticalArrangement = Arrangement.spacedBy(40.dp)) {
        Title(text = stringResource(R.string.score))
        Score(text = "$leftScore : $rightScore")
        Row (modifier = Modifier.fillMaxWidth()){
            AddScoreButton {
                leftScore += 1
            }
            Spacer(modifier = Modifier.weight(1f))
            AddScoreButton {
                rightScore += 1
            }
        }
        ResetButton {
            leftScore = 0
            rightScore = 0
        }
        Button(onClick = { navController.navigate(Screens.TeamsScreen.route)}) {
            Text(stringResource(R.string.go_to_teams))
        }
    }
}

@Composable
fun ResetButton(onClick: () -> Unit) {
    Button(onClick = onClick) {
        Text(stringResource(R.string.reset_score))
    }
}

@Composable
fun AddScoreButton(onClick: () -> Unit) {
    Button(onClick = onClick) {
        Text(stringResource(R.string._1))
    }
}

@Composable
fun Score(text: String) {
    Text(
        text = text,
        fontSize = 42.sp,
        fontWeight = FontWeight.Bold
    )
}

@Composable
fun Title(text: String) {
    Text(
        text = text,
        fontSize = 30.sp
    )
}
