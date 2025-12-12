
import { inject } from '@angular/core';
import { ActivatedRouteSnapshot, CanActivateFn, Router, RouterStateSnapshot, UrlTree } from '@angular/router';
import { jwtDecode } from 'jwt-decode';
import { Observable } from 'rxjs';

export const userAuthGuard: CanActivateFn = (
  route: ActivatedRouteSnapshot,
  state: RouterStateSnapshot
): Observable<boolean | UrlTree> | Promise<boolean | UrlTree> | boolean | UrlTree => {

  const token = localStorage.getItem('access_token');
  const router = inject(Router)

  if(!token){
    router.navigate(['/'])
    return false
  }
  console.log(token)
  const isExpired = isTokenExpired(token)
  if(isExpired){
    router.navigate(['/'])
    return false
  }
  return true
};


export function isTokenExpired(token: string): boolean {
  try {
    const decodedToken: any = jwtDecode(token);
    const expirationTime = decodedToken.exp * 1000; // Convert seconds to milliseconds
    const currentTime = new Date().getTime();
    console.log(expirationTime)
    console.log(currentTime)
    return expirationTime < currentTime;
  } catch (error) {
    // Handle decoding errors
    return true;
  }
}