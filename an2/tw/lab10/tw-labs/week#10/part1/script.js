/** ⚡ DEMO: JS crash-course 🚓 */

let total = '123 dollars'; // variable declaration
total = 22; 

console.log(document.body); // print to the console + document object


/** EX #1: using DOM methods add the following elements in the HTML's body 
 * 
 * body
 *  .gallery
 *      img: src, alt
 *      img: src, alt
 *      img: src, alt
*/

/** 💻 Code #1 💻 */
let gallery = document.createElement("div");
gallery.setAttribute("class", "gallery");
document.body.appendChild(gallery);
for (let i = 0 ; i < 3; ++i){
    let img = document.createElement("img");
    img.setAttribute("src", "https://vokrug.tv/pic/news/f/3/9/5/f3958440047a259d3b1a4da87ece2394.jpg");
    img.setAttribute("alt", "Arnold");
    gallery.appendChild(img);
}
/** ⚡ DEMO accessing the DOM & event listeners */


/** EX #2: 
 *   - add a click event listener on every image that prints a message to the console 
*/

/** 💻 Code  #2 💻  */
// let imgs = document.getElementsByTagName("img");
// for (let i = 0; i < imgs.length; ++i)
//     imgs[i].addEventListener("click", function(){
//         if (imgs[i].getAttribute("alt") === "Arnold"){
//             imgs[i].setAttribute("src", "http://images.mentalfloss.com/sites/default/files/styles/mf_image_16x9/public/rambo.jpg?itok=36OqRSme&resize=1100x619");
//             imgs[i].setAttribute("alt", "Rambo");
//         }
//         else{
//             imgs[i].setAttribute("src", "https://vokrug.tv/pic/news/f/3/9/5/f3958440047a259d3b1a4da87ece2394.jpg");
//             imgs[i].setAttribute("alt", "Arnold");
//         }
//     });
/** ⚡ DEMO removing event listeners */

/** EX #3:  add a click event listener on the gallery that prints a message to the console
 * 
*/

/** 💻 Code #3 💻 */
function onGalleryClick(e){
    console.log(e.target);
    if (e.target.tagName === "IMG"){
        console.log("click pe img");
    }
}

gallery.addEventListener("click", onGalleryClick);//al treilea parametru e sa faca trigger la capture, nu la bubble
// gallery.removeEventListener("click", onGalleryClick);

//  🤚 Q&A: which one triggered first? Bubble vs capture


/** ⚡ DEMO:  a more efficient way of handling multiple event listeners */

document.querySelectorAll(".gallery > img");
$x("/html/body/div[@class='gallery']/img");