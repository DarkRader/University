package cz.cvut.kuznear1.footballapp.screen

import androidx.compose.foundation.clickable
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.layout.size
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.foundation.shape.CircleShape
import androidx.compose.material.icons.Icons
import androidx.compose.material.icons.filled.ArrowBack
import androidx.compose.material.icons.filled.ArrowForward
import androidx.compose.material3.CenterAlignedTopAppBar
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.Icon
import androidx.compose.material3.IconButton
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.draw.clip
import androidx.compose.ui.layout.ContentScale
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import androidx.navigation.NavController
import coil.compose.AsyncImage
import cz.cvut.kuznear1.footballapp.R
import cz.cvut.kuznear1.footballapp.Screens
import cz.cvut.kuznear1.footballapp.model.Team
import cz.cvut.kuznear1.footballapp.model.teams


@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun TeamsScreen(navController: NavController) {
    Scaffold(
        topBar = {
            CenterAlignedTopAppBar(
                title = { Text(stringResource(R.string.teams)) },
                navigationIcon = {
                    IconButton(onClick = { navController.navigateUp() }) {
                        Icon(
                            imageVector = Icons.Default.ArrowBack,
                            contentDescription = null
                        )
                    }
                }
            )
        }
    ) {
        LazyColumn(modifier = Modifier.padding(it)) {
            items(teams) { team ->
                TeamItem(team) {
                    navController.navigate(Screens.DetailScreen.route + "/${team.id}")
                }
            }
        }
    }
}

@Composable
fun TeamItem(
    team: Team,
    onTeamClick: () -> Unit,
) {
    Row(modifier = Modifier.fillMaxWidth().padding(8.dp).clickable { onTeamClick() }) {
        AsyncImage(
            modifier = Modifier.size(64.dp).padding(8.dp).clip(CircleShape),
            model = team.logoUrl,
            contentScale = ContentScale.Crop,
            contentDescription = null,
        )
        Text(
            text = team.name,
            fontSize = 25.sp,
            modifier = Modifier.weight(1f)
        )
        Icon(imageVector = Icons.Default.ArrowForward, contentDescription = null)
    }
}

