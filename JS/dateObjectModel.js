var today = new Date();
var year = today.getFullYear();
var birthdate = new Date('October 22, 1993 08:00:00');

var age = today.getTime() - birthdate.getTime();
age = Math.floor( age / 31556900000);

msg = '<p>My age is: ' + age + 'years </p>';
var element = document.getElementById('info');
element.innerHTML = msg;

var ft = document.getElementById('foot');
ft.innerHTML = '<p>Copyright &copy' + year + 'Shiv Sandhu</p>';
