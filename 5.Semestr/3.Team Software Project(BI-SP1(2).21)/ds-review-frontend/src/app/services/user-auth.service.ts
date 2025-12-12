
import { Injectable } from '@angular/core';
import { NavigationExtras, Router } from '@angular/router';
import { ApiService } from './api.service';
import { ApiPostRegistration } from 'src/app/objects/api-post-registration';
import { BehaviorSubject, Subject, lastValueFrom,Observable, catchError, map, of } from 'rxjs';



@Injectable({
  providedIn: 'root'
})
export class UserAuthService {

  constructor(
    private apiService: ApiService,
    private router: Router
  ) {}
  
  goToRegistration(){
    this.router.navigate(['/registration']);
  }

  async registerUser(firstName: string,lastName: string,username: string,password: string,email: string): Promise<Boolean> {
    const registrationData: ApiPostRegistration = {
      username: username,
      first_name: firstName,
      last_name: lastName,
      email: email,
      password: password
    };
  
    return await lastValueFrom(this.apiService.postRegistration(registrationData).pipe(
      map(() => true),
      catchError(() => of(false))
    ));
  }

  async login(username: string, password: string): Promise<Boolean>{
    const loginData = `grant_type=&username=${encodeURIComponent(username)}&password=${encodeURIComponent(password)}&scope=&client_id=&client_secret=`;
    return await lastValueFrom(this.apiService.postLogin(loginData).pipe(
      map((response:any) => {
        this.storeToken(response.access_token)
        return true;
      }),
      catchError((error) => {
        return of(false);
      })
    ))
  }

  logout(){
    localStorage.removeItem('access_token');
    this.router.navigate(['/']);
  }

  private storeToken(token: string): void {
    // Store the token securely (you can use localStorage, a service, or a cookie)
    localStorage.setItem('access_token', token);
  }
}
