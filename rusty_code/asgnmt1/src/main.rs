use nix::sys::wait::wait;
use nix::unistd::ForkResult::{Child, Parent};
use nix::unistd::{fork, getpid, getppid};
use std::process;


fn main() {
    println!("Hello, world!");

    let pid = unsafe{ (fork()) };

    //println!("{}", pid);
    //
    //
    match pid.expect("error message") {

        Child => { println!("yo im child, pamper me XD! {} is my process id and my parents id is {}", getpid(), getppid()); 
        process::exit(0);
        }, 

        Parent {child} => {


            wait();

            println!("IM THE PARENT, IVE WAITED ENOUGH! {} is my id and {} is my child", getpid(), child);
        }
        


    }
}

