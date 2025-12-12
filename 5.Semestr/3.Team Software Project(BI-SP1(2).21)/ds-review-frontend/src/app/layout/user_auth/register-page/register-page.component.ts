import { Component } from '@angular/core';
import { UserAuthService } from '../../../services/user-auth.service';
import { FormGroup, FormBuilder, Validators } from '@angular/forms';
import { Router } from '@angular/router';

@Component({
  selector: 'app-register-page',
  templateUrl: './register-page.component.html',
  styleUrls: ['./register-page.component.scss']
})
export class RegisterPageComponent {
  registrationForm: FormGroup;

  constructor(
    private fb: FormBuilder,
    private userAuthService: UserAuthService,
    private router: Router) {

    this.registrationForm = this.fb.group({
      first_name: ['', Validators.required],
      last_name: ['', Validators.required],
      username: ['', Validators.required],
      password: ['', Validators.required],
      email: ['', [Validators.required, Validators.email]],
    });
  }

  async register() {
    if(!this.registrationForm.valid){
      alert("INVALID FORM")
      return
    }
    const { first_name, last_name, username, password, email } = this.registrationForm.value;
    try{
      const success = await this.userAuthService.registerUser(first_name, last_name, username, password, email)
      if (success) {
        this.handleResponseRegistration()
      } else {
        this.handleError()
      }
    }catch(error){
      this.handleError()
    }
  }

  private handleResponseRegistration(){
    alert("SUCCESSFULLY REGISTERED!")
    this.router.navigate(['/']);
  }

  private handleError(){
    // Handle registration errors
    alert("OPERATION DID NOT SUCCEED")
    this.router.navigate(['/']);
  }
  
}
