import { Component } from '@angular/core';
import { UserAuthService } from '../../../services/user-auth.service';
import { Location } from '@angular/common';
import { NavigationExtras, Router } from '@angular/router';

@Component({
  selector: 'app-login-page',
  templateUrl: './login-page.component.html',
  styleUrls: ['./login-page.component.scss']
})
export class LoginPageComponent {
  username = '';
  password = '';

  constructor(private userAuthService: UserAuthService,private location: Location,private router: Router,) {}

  async login() {
    try{
      const success = await this.userAuthService.login(this.username, this.password)
      if(success){
        this.handleSuccessLogin()
      }else{
        this.handleFailLogin()
      }
    }catch(error){
      this.handleFailLogin()
    }
  }

  register() {
    this.userAuthService.goToRegistration();
  }

  private handleSuccessLogin(){
    this.location.replaceState('/me');
    const navigationExtras: NavigationExtras = { replaceUrl: true };
    this.router.navigate(['/me'],navigationExtras);
  }

  private handleFailLogin(){
    alert("LOGIN NOT SUCCESSFULL")
  }

}
