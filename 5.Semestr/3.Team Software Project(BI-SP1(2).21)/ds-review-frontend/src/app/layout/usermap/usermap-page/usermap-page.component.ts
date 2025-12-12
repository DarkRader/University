import { Component, OnInit } from '@angular/core';
import { UsermapService } from '../../../services/usermap.service';
import { UserData } from 'src/app/objects/user-data';
import { Router } from '@angular/router';
import { UserAuthService } from '../../../services/user-auth.service';
import { Clipboard } from '@angular/cdk/clipboard';

@Component({
  selector: 'app-usermap-page',
  templateUrl: './usermap-page.component.html',
  styleUrls: ['./usermap-page.component.scss']
})
export class UsermapPageComponent implements OnInit{
  
  userData: UserData | undefined

  constructor(private usermapService: UsermapService, private router: Router,
    private userAuthService: UserAuthService,private clipboard: Clipboard){

  }

  ngOnInit(): void {
    this.usermapService.getUserData()
    
    this.usermapService.userData$.subscribe((userData) => {
      this.userData = userData;
      console.log(this.userData)
    });
  }

  goToDocuments(){
    this.router.navigate(['/documents'])
  }

  logout(){
    this.userAuthService.logout()
  }

  goToDocSubmission(){
    this.router.navigate(['documents/submit'])
  }

  copyToClipboard(text: string | undefined): void {
    if (text) {
      this.clipboard.copy(text);
    }
  }


}
