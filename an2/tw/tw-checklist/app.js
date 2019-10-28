document.getElementById('todos').addEventListener('click', function onClick(e) {
    if (e.target.type === 'checkbox') {
        updateToDo(function () {
            showNotication('Todo\'s successfully updated!');
        });
    }
});




/** FUNCTIONS */

function showNotication(text) {
    var notificationEl = document.getElementById('notification');

    notificationEl.innerText = text;
    notificationEl.classList.add('visible');
    setTimeout(function hideNotification() {
        notificationEl.classList.remove('visible');
    }, 2500);
}

function updateToDo(callback) {
    setTimeout(callback, 1000);
}