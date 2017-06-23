		var elUsername = document.getElementById('username');
		var elMsg = document.getElementById('feedback');
		
		function checkUsername(){
		
			if (elUsername.value.length <7){
				elMsg.innerHTML = 'Uersname length must be 7 characters';
			} else {
				elMsg.innerHTML = '';
			}
		}
		
		elUsername.addEventListener('blur', checkUsername, false);
		
		
		var elPassword = document.getElementById('pass');
		function checkPassword(){
		
			if (elPassword.value.length <7){
				elMsg.innerHTML = 'Password length must be 7 characters';
			} else {
				elMsg.innerHTML = '';
			}
		}
		elPassword.addEventListener('blur', checkPassword, false);
		
		function setup(){
			var textInput;
			textInput = document.getElementById('username');
			textInput.focus();
		}
		
		window.addEventListener('load', setup, false);